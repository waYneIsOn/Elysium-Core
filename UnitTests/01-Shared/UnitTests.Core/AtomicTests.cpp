#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/UnorderedMap.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Convert.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Threading/Atomic.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Threading/Thread.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Threading
{
	TEST_CLASS(AtomicTests)
	{
	public:
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
				Elysium::Core::Template::Container::Delegate<void, void*> ThreadStart =
					Elysium::Core::Template::Container::Delegate<void, void*>::Bind<AtomicTests, &AtomicTests::Increment>(*this);

				Elysium::Core::Template::Container::Vector<Elysium::Core::Threading::Thread> Threads =
					Elysium::Core::Template::Container::Vector<Elysium::Core::Threading::Thread>(_NumberOfThreads);
				Threads.Clear();
				for (Elysium::Core::size i = 0; i < _NumberOfThreads; i++)
				{
					Threads.PushBack(Elysium::Core::Threading::Thread(ThreadStart));
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
						Logger::WriteMessage("\r\nDuplicate value ");
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

			Elysium::Core::uint32_t Index = 1;
			for (Elysium::Core::Template::Container::UnorderedMap<Elysium::Core::uint32_t, Elysium::Core::uint32_t>::FIterator Iterator = UniqueValues.GetBegin();
				Iterator != UniqueValues.GetEnd(); ++Iterator)
			{
				Elysium::Core::Template::Container::LinkedListNode<Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::uint32_t, Elysium::Core::uint32_t>>* Node = *Iterator;
				Elysium::Core::Template::Container::KeyValuePair<Elysium::Core::uint32_t, Elysium::Core::uint32_t>& Item = Node->GetItem();
				/*
				Logger::WriteMessage(&Elysium::Core::Template::Text::Convert<char>::ToString(Item.GetValue())[0]);
				Logger::WriteMessage("\r\n");
				*/
				Assert::AreEqual(Index, Item.GetValue());
				Index++;
			}
		}
	private:
		void Increment(void* Input)
		{
			for (Elysium::Core::Template::System::size i = 0; i < _NumberOfIncrements; i++)
			{
				_Counter++;

				// between reading PreviousValue and CurrentValue all the other threads could have incremented the internal value
				// therefore it doesn't make sense to store PreviousValue
				// how to determine whether Load() still locks correctly?
				//Elysium::Core::Template::System::uint32_t PreviousValue = _AtomicCounter;
				Elysium::Core::Template::System::uint32_t PreviousValue = _AtomicCounter.Load();

				Elysium::Core::Template::System::uint32_t CurrentValue = _AtomicCounter++;
				static_cast<Elysium::Core::Template::Container::Vector<int>*>(Input)->PushBack(CurrentValue);

				_AtomicPointer++;
			}
		}
	private:
		const Elysium::Core::uint32_t _NumberOfThreads = 10;
		const Elysium::Core::uint32_t _NumberOfIncrements = 100000;

		Elysium::Core::Template::System::uint32_t _Counter;
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t> _AtomicCounter;

		Elysium::Core::Template::System::uint32_t _AtomicPointerStorage = 0;
		Elysium::Core::Template::Threading::Atomic<Elysium::Core::Template::System::uint32_t*> _AtomicPointer;
	};
}
