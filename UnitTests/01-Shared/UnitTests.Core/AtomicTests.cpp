#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/UnorderedMap.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Threading/Atomic.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Threading::SynchronizationPrimitives
{
	enum class EnumForAtomics
	{
		Value1,
		Value2,
		Value3
	};

	TEST_CLASS(AtomicTests)
	{
	public:
		TEST_METHOD(Construction)
		{
			// default construction
			Elysium::Core::Template::Threading::Atomic<bool> DefaultAtomicBoolean;
			Elysium::Core::Template::Threading::Atomic<void*> DefaultAtomicPointer;
			Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t> DefaultAtomicUInt32;
			Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int32_t> DefaultAtomicInt32;

			Assert::IsFalse(DefaultAtomicBoolean.Load());
			Assert::IsNull(DefaultAtomicPointer.Load());
			Assert::AreEqual(0_ui32, DefaultAtomicUInt32.Load());
			Assert::AreEqual(0, DefaultAtomicInt32.Load());

			// construction with given value
			Elysium::Core::Template::Threading::Atomic<bool> AtomicBoolean(true);
			Elysium::Core::Template::Threading::Atomic<void*> AtomicPointer(reinterpret_cast<void*>(0x01));
			Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t> AtomicUInt32(1337);
			Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int32_t> AtomicInt32(-5448);

			Assert::IsTrue(AtomicBoolean.Load());
			Assert::AreEqual(reinterpret_cast<void*>(0x01), AtomicPointer.Load());
			Assert::AreEqual(1337_ui32, AtomicUInt32.Load());
			Assert::AreEqual(-5448, AtomicInt32.Load());
		}

		TEST_METHOD(IncrementCountersInParallel)
		{
			_Counter = 0;
			_AtomicCounter = 0;
			_AtomicPointerStorage = 0;
			_AtomicPointer = &_AtomicPointerStorage;

			// each thread having it's own vector to gather values means there shouldn't be any interference (except for some delay)
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Container::Vector<Elysium::Core::uint32_t>> GatheredValues =
				Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Container::Vector<Elysium::Core::uint32_t>>(_NumberOfThreads);
			GatheredValues.Clear();
			for (Elysium::Core::size i = 0; i < _NumberOfThreads; i++)
			{
				GatheredValues.PushBack(Elysium::Core::Template::Container::Vector<Elysium::Core::uint32_t>());
			}

			// ...
			{
				Elysium::Core::Template::Container::Delegate<void, void*> ParameterizedThreadStart =
					Elysium::Core::Template::Container::Delegate<void, void*>::Bind<AtomicTests, &AtomicTests::Increment>(*this);

				Elysium::Core::Template::Container::Vector<Elysium::Core::Threading::Thread> Threads =
					Elysium::Core::Template::Container::Vector<Elysium::Core::Threading::Thread>(_NumberOfThreads);
				Threads.Clear();
				for (Elysium::Core::size i = 0; i < _NumberOfThreads; i++)
				{
					Threads.PushBack(Elysium::Core::Threading::Thread(ParameterizedThreadStart));
				}

				for (Elysium::Core::size i = 0; i < _NumberOfThreads; i++)
				{
					Threads[i].Start(static_cast<void*>(&GatheredValues[i]));
				}
			}

			Logger::WriteMessage("Counter: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(_Counter)[0]);
			Logger::WriteMessage("\r\nAtomic counter: ");
			Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(_AtomicCounter)[0]);
			Logger::WriteMessage("\r\n");

			Assert::IsTrue(_Counter < _NumberOfThreads * _NumberOfIncrements);
			Assert::IsTrue(_AtomicCounter == _NumberOfThreads * _NumberOfIncrements);
			Assert::IsTrue(*_AtomicPointer.Load() == _AtomicCounter);

			// gather all values in a hashtable to check for duplicate values
			Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::uint32_t, Elysium::Core::uint32_t> UniqueValues =
				Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::uint32_t, Elysium::Core::uint32_t>(_NumberOfThreads * _NumberOfIncrements);
			for (Elysium::Core::size i = 0; i < _NumberOfThreads; i++)
			{
				for (Elysium::Core::size j = 0; j < GatheredValues[i].GetLength(); j++)
				{
					Elysium::Core::uint32_t Value = GatheredValues[i][j];

					// adding a key that already exists would throw an ArgumentException meaning my atomics don't work correctly
					try
					{
						UniqueValues.Add(Value, Value);
					}
					catch (const Elysium::Core::ArgumentException& ex)
					{
						Logger::WriteMessage("Duplicate value ");
						Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(Value)[0]);
						Logger::WriteMessage(" in thread ");
						Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(i)[0]);
						Logger::WriteMessage("\r\n");
						throw;
					}
				}

				GatheredValues[i].Clear();
				GatheredValues[i].ShrinkToFit();
			}

			Elysium::Core::uint32_t Index = 0;
			for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::uint32_t, Elysium::Core::uint32_t>::FIterator Iterator = UniqueValues.GetBegin();
				Iterator != UniqueValues.GetEnd(); ++Iterator)
			{
				Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::uint32_t, Elysium::Core::uint32_t>>* Node = *Iterator;
				Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::uint32_t, Elysium::Core::uint32_t>& Item = Node->GetItem();
				
				//Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(Item.GetValue())[0]);
				//Logger::WriteMessage("\r\n");
				
				Assert::AreEqual(Index, Item.GetValue());
				Index++;
			}
		}

		TEST_METHOD(MultiThreadedStore)
		{
			_MultiThreadedLoadAndStoreAtomic = 0;

			Elysium::Core::Template::Container::Delegate<void, void*> ParameterizedThreadStart =
				Elysium::Core::Template::Container::Delegate<void, void*>::Bind<AtomicTests, &AtomicTests::StoreValue>(*this);

			Elysium::Core::int32_t Value1 = 111;
			Elysium::Core::int32_t Value2 = 222;
			Elysium::Core::int32_t Value3 = 333;

			Elysium::Core::Threading::Thread Thread1 = Elysium::Core::Threading::Thread(ParameterizedThreadStart);
			Elysium::Core::Threading::Thread Thread2 = Elysium::Core::Threading::Thread(ParameterizedThreadStart);
			Elysium::Core::Threading::Thread Thread3 = Elysium::Core::Threading::Thread(ParameterizedThreadStart);

			Thread1.Start(reinterpret_cast<void*>(&Value1));
			Thread2.Start(reinterpret_cast<void*>(&Value2));
			Thread3.Start(reinterpret_cast<void*>(&Value3));

			Thread1.Join();
			Thread2.Join();
			Thread3.Join();

			Elysium::Core::int32_t LoadedValue = _MultiThreadedLoadAndStoreAtomic.Load();

			Assert::IsTrue(
				LoadedValue == Value1 ||
				LoadedValue == Value2 ||
				LoadedValue == Value3
			);
		}

		TEST_METHOD(MultiThreadedLoad)
		{
			_AtomicBool = true;

			Elysium::Core::Template::Container::Delegate<void> LoadingThreadStart =
				Elysium::Core::Template::Container::Delegate<void>::Bind<AtomicTests, &AtomicTests::LoadValue>(*this);

			Elysium::Core::Threading::Thread LoadingThread1 = Elysium::Core::Threading::Thread(LoadingThreadStart);
			Elysium::Core::Threading::Thread LoadingThread2 = Elysium::Core::Threading::Thread(LoadingThreadStart);
			Elysium::Core::Threading::Thread LoadingThread3 = Elysium::Core::Threading::Thread(LoadingThreadStart);
			Elysium::Core::Threading::Thread LoadingThread4 = Elysium::Core::Threading::Thread(LoadingThreadStart);
			Elysium::Core::Threading::Thread LoadingThread5 = Elysium::Core::Threading::Thread(LoadingThreadStart);
			Elysium::Core::Threading::Thread LoadingThread6 = Elysium::Core::Threading::Thread(LoadingThreadStart);

			LoadingThread1.Start();
			LoadingThread2.Start();
			LoadingThread3.Start();
			LoadingThread4.Start();
			LoadingThread5.Start();
			LoadingThread6.Start();

			LoadingThread1.Join();
			LoadingThread2.Join();
			LoadingThread3.Join();
			LoadingThread4.Join();
			LoadingThread5.Join();
			LoadingThread6.Join();

			const bool LoadedValue = _AtomicBool.Load();
			Assert::IsTrue(LoadedValue);
		}

		TEST_METHOD(MultiThreadedStoreAndLoad)
		{
			_MultiThreadedLoadAndStoreAtomic = 0;

			Elysium::Core::Template::Container::Delegate<void, void*> StoringThreadStart =
				Elysium::Core::Template::Container::Delegate<void, void*>::Bind<AtomicTests, &AtomicTests::SimulateWorkAndStoreValue>(*this);

			Elysium::Core::Template::Container::Delegate<void> LoadingThreadStart =
				Elysium::Core::Template::Container::Delegate<void>::Bind<AtomicTests, &AtomicTests::SimulateWorkAndLoad>(*this);

			Elysium::Core::int32_t StoringValue = 1337;

			Elysium::Core::Threading::Thread StoringThread = Elysium::Core::Threading::Thread(StoringThreadStart);
			Elysium::Core::Threading::Thread LoadingThread = Elysium::Core::Threading::Thread(LoadingThreadStart);

			StoringThread.Start(reinterpret_cast<void*>(&StoringValue));
			LoadingThread.Start();

			StoringThread.Join();
			LoadingThread.Join();

			const Elysium::Core::int32_t LoadedValue = _MultiThreadedLoadAndStoreAtomic.Load();
			Assert::AreEqual(StoringValue, LoadedValue);
		}
	private:
		void Increment(void* Input)
		{
			for (Elysium::Core::Template::System::size i = 0; i < _NumberOfIncrements; i++)
			{
				_Counter++;

				// how to determine whether Load() still locks correctly?
				//Elysium::Core::Template::System::uint32_t LoadedValue = _AtomicCounter;
				//Elysium::Core::Template::System::uint32_t LoadedValue = _AtomicCounter.Load();

				Elysium::Core::Template::System::uint32_t PreviousValue = _AtomicCounter++;
				static_cast<Elysium::Core::Template::Container::Vector<int>*>(Input)->PushBack(PreviousValue);

				_AtomicPointer++;
			}
		}

		void StoreValue(void* Input)
		{
			const Elysium::Core::int32_t Value = *reinterpret_cast<const Elysium::Core::int32_t*>(Input);

			_MultiThreadedLoadAndStoreAtomic.Store(Value);
		}

		void LoadValue()
		{
			const bool LoadedValue = _AtomicBool.Load();
			Assert::IsTrue(LoadedValue);
		}

		void SimulateWorkAndStoreValue(void* Input)
		{
			Elysium::Core::Threading::Thread::Sleep(Elysium::Core::TimeSpan::FromTicks(1000000));
			const Elysium::Core::int32_t Value = *reinterpret_cast<const Elysium::Core::int32_t*>(Input);
			_MultiThreadedLoadAndStoreAtomic.Store(Value);
		}

		void SimulateWorkAndLoad()
		{
			Elysium::Core::Threading::Thread::Sleep(Elysium::Core::TimeSpan::FromTicks(500000));
			const Elysium::Core::int32_t Value = _MultiThreadedLoadAndStoreAtomic.Load();
		}
	private:
		const Elysium::Core::uint32_t _NumberOfThreads = 10;
		const Elysium::Core::uint32_t _NumberOfIncrements = 100000;

		Elysium::Core::Template::System::uint32_t _Counter;
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t> _AtomicCounter;

		Elysium::Core::Template::System::uint32_t _AtomicPointerStorage = 0;
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t*> _AtomicPointer;
	private:
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::int32_t> _MultiThreadedLoadAndStoreAtomic;
	private:
		Elysium::Core::Template::Threading::Atomic<bool> _AtomicBool;
	};
}
