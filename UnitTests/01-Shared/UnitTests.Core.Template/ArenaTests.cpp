#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core.Template/Literals.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/Memory/Scoped/Arena.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Memory::Scoped
{
	struct TrivialStruct
	{
		Elysium::Core::Template::System::int32_t _SomeInt;
		bool _SomeBool;
	};

	class NonTrivialBaseClass
	{
	public:
		NonTrivialBaseClass()
			: _IsDestructed(false)
		{ }

		NonTrivialBaseClass(const NonTrivialBaseClass& Source) = delete;

		NonTrivialBaseClass(NonTrivialBaseClass&& Source) = delete;

		~NonTrivialBaseClass()
		{
			_IsDestructed = true;
		}
	public:
		bool _IsDestructed;
	};

	class NonTrivialClass
		: public NonTrivialBaseClass
	{
	public:
		NonTrivialClass()
			: NonTrivialBaseClass()
		{ }

		NonTrivialClass(const NonTrivialClass& Source) = delete;

		NonTrivialClass(NonTrivialClass&& Source) = delete;

		~NonTrivialClass()
		{

		}
	/*
	public:
		void* operator new(Elysium::Core::Template::System::size Size)
		{
			void* InstancePointer = malloc(Size);
			::new (InstancePointer) NonTrivialClass();


			//new (&_Data[i]) T();

			return InstancePointer;
		}

		void operator delete(void* InstancePointer)
		{
			free(InstancePointer);
		}
	*/
	};

	TEST_CLASS(ArenaTests)
	{
	public:
		TEST_METHOD(OddSizes)
		{
			// "large" arena
			{
				constexpr Elysium::Core::Template::Memory::Scoped::ArenaOptions LargeOptions =
					Elysium::Core::Template::Memory::Scoped::ArenaOptions(1024, 1, false, false);
				Elysium::Core::Template::Memory::Scoped::Arena LargeArena = Elysium::Core::Template::Memory::Scoped::Arena(LargeOptions);

				// ...
				void* AllocatedMemory1 = LargeArena.Push(3, 4);
				Assert::AreEqual(1_ui64, LargeArena.GetNumberOfPages());
				Assert::AreEqual(1024_ui64, LargeArena.GetCapacity());
				Assert::AreEqual(3_ui64, LargeArena.GetSize());
				Assert::IsNotNull(AllocatedMemory1);

				// ...
				void* AllocatedMemory2 = LargeArena.Push(21, 4);
				Assert::AreEqual(1_ui64, LargeArena.GetNumberOfPages());
				Assert::AreEqual(1024_ui64, LargeArena.GetCapacity());
				Assert::AreEqual(25_ui64, LargeArena.GetSize());
				Assert::IsNotNull(AllocatedMemory2);

				// ...
				void* AllocatedMemory3 = LargeArena.Push(1, 4);
				Assert::AreEqual(1_ui64, LargeArena.GetNumberOfPages());
				Assert::AreEqual(1024_ui64, LargeArena.GetCapacity());
				Assert::AreEqual(29_ui64, LargeArena.GetSize());
				Assert::IsNotNull(AllocatedMemory3);

				// ...
				void* AllocatedMemory4 = LargeArena.Push(2, 4);
				Assert::AreEqual(1_ui64, LargeArena.GetNumberOfPages());
				Assert::AreEqual(1024_ui64, LargeArena.GetCapacity());
				Assert::AreEqual(34_ui64, LargeArena.GetSize());
				Assert::IsNotNull(AllocatedMemory3);

				// ...
				LargeArena.Clear();
				Assert::AreEqual(1_ui64, LargeArena.GetNumberOfPages());
				Assert::AreEqual(1024_ui64, LargeArena.GetCapacity());
				Assert::AreEqual(0_ui64, LargeArena.GetSize());

				// ...
				void* AllocatedMemory5 = LargeArena.Push(3, 1);
				Assert::AreEqual(1_ui64, LargeArena.GetNumberOfPages());
				Assert::AreEqual(1024_ui64, LargeArena.GetCapacity());
				Assert::AreEqual(3_ui64, LargeArena.GetSize());
				Assert::IsNotNull(AllocatedMemory5);

				// ...
				void* AllocatedMemory6 = LargeArena.Push(21, 1);
				Assert::AreEqual(1_ui64, LargeArena.GetNumberOfPages());
				Assert::AreEqual(1024_ui64, LargeArena.GetCapacity());
				Assert::AreEqual(24_ui64, LargeArena.GetSize());
				Assert::IsNotNull(AllocatedMemory6);

				// ...
				void* AllocatedMemory7 = LargeArena.Push(1000, 1);
				Assert::AreEqual(1_ui64, LargeArena.GetNumberOfPages());
				Assert::AreEqual(1024_ui64, LargeArena.GetCapacity());
				Assert::AreEqual(1024_ui64, LargeArena.GetSize());
				Assert::IsNotNull(AllocatedMemory7);
			}

			// small arena
			{
				constexpr Elysium::Core::Template::Memory::Scoped::ArenaOptions SmallOptions =
					Elysium::Core::Template::Memory::Scoped::ArenaOptions(1, 1, false, false);
				Elysium::Core::Template::Memory::Scoped::Arena SmallArena = Elysium::Core::Template::Memory::Scoped::Arena(SmallOptions);
				Assert::AreEqual(1_ui64, SmallArena.GetNumberOfPages());
				Assert::AreEqual(1_ui64, SmallArena.GetCapacity());
				Assert::AreEqual(0_ui64, SmallArena.GetSize());

				// pop a single element (to ensure nothing happens)
				SmallArena.Pop<TrivialStruct>();
				Assert::AreEqual(1_ui64, SmallArena.GetNumberOfPages());
				Assert::AreEqual(1_ui64, SmallArena.GetCapacity());
				Assert::AreEqual(0_ui64, SmallArena.GetSize());

				// reset the arena
				SmallArena.Reset();
				Assert::AreEqual(1_ui64, SmallArena.GetNumberOfPages());
				Assert::AreEqual(1_ui64, SmallArena.GetCapacity());
				Assert::AreEqual(0_ui64, SmallArena.GetSize());

				// push no elements
				Elysium::Core::Template::System::int32_t* AllocatedInstanceSmall0 = SmallArena.Push<Elysium::Core::Template::System::int32_t>(0);
				Assert::AreEqual(1_ui64, SmallArena.GetNumberOfPages());
				Assert::AreEqual(1_ui64, SmallArena.GetCapacity());
				Assert::AreEqual(0_ui64, SmallArena.GetSize());
				Assert::IsNull(AllocatedInstanceSmall0);

				// push three bytes (NO alignment!)
				void* AllocatedMemorySmall0 = SmallArena.Push(3, 3);
				Assert::AreEqual(1_ui64, SmallArena.GetNumberOfPages());
				Assert::AreEqual(1_ui64, SmallArena.GetCapacity());
				Assert::AreEqual(0_ui64, SmallArena.GetSize());
				Assert::IsNull(AllocatedMemorySmall0);

				// push three bytes (forcing "resize")
				void* AllocatedMemorySmall1 = SmallArena.Push(3);
				Assert::AreEqual(2_ui64, SmallArena.GetNumberOfPages());
				Assert::AreEqual(4_ui64, SmallArena.GetCapacity());
				Assert::AreEqual(4_ui64, SmallArena.GetSize());
				Assert::IsNotNull(AllocatedMemorySmall1);

				// assign more bytes at once than defined page-size (forcing "resize")
				void* AllocatedMemorySmall2 = SmallArena.Push(25);
				Assert::AreEqual(3_ui64, SmallArena.GetNumberOfPages());
				Assert::AreEqual(29_ui64, SmallArena.GetCapacity());
				Assert::AreEqual(29_ui64, SmallArena.GetSize());
				Assert::IsNotNull(AllocatedMemorySmall2);

				// push one byte (forcing "resize")
				void* AllocatedMemorySmall3 = SmallArena.Push(1);
				Assert::AreEqual(4_ui64, SmallArena.GetNumberOfPages());
				Assert::AreEqual(30_ui64, SmallArena.GetCapacity());
				Assert::AreEqual(30_ui64, SmallArena.GetSize());
				Assert::IsNotNull(AllocatedMemorySmall3);
			}
		}

		TEST_METHOD(ComplexTypeOnly)
		{
			auto siiiii = sizeof(NonTrivialClass);
			auto aliiiiii = sizeof(NonTrivialClass);

			constexpr Elysium::Core::Template::Memory::Scoped::ArenaOptions Options = Elysium::Core::Template::Memory::Scoped::ArenaOptions(
				sizeof(NonTrivialClass) * 2, 1, false, false);
			Elysium::Core::Template::Memory::Scoped::Arena ArenaAllocator = Elysium::Core::Template::Memory::Scoped::Arena(Options);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(2_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// push a single element
			void* AllocatedMemory0 = ArenaAllocator.Push(sizeof(NonTrivialClass), alignof(NonTrivialClass));
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(2_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(1_ui64, ArenaAllocator.GetSize());
			Assert::IsNotNull(AllocatedMemory0);
			NonTrivialClass* AllocatedInstance0 = ::new (AllocatedMemory0) NonTrivialClass();
			Assert::IsFalse(AllocatedInstance0->_IsDestructed);

			// push another element
			void* AllocatedMemory1 = ArenaAllocator.Push(sizeof(NonTrivialClass), alignof(NonTrivialClass));
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(2_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(2_ui64, ArenaAllocator.GetSize());
			Assert::IsNotNull(AllocatedMemory1);
			NonTrivialClass* AllocatedInstance1 = ::new (AllocatedMemory1) NonTrivialClass();
			Assert::IsFalse(AllocatedInstance1->_IsDestructed);

			// clear the arena (causing a memory leak if NonTrivialClass owns heap allocated memory)
			ArenaAllocator.Clear();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(2_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// fix the memory leak (which can be done in this case)
			AllocatedInstance0->~NonTrivialClass();
			AllocatedInstance1->~NonTrivialClass();
			Assert::IsTrue(AllocatedInstance0->_IsDestructed);
			Assert::IsTrue(AllocatedInstance1->_IsDestructed);
		}

		TEST_METHOD(IntegersOnly)
		{
			constexpr const Elysium::Core::Template::System::size TotalNumberOfElements = 20;

			constexpr Elysium::Core::Template::Memory::Scoped::ArenaOptions Options = Elysium::Core::Template::Memory::Scoped::ArenaOptions(
				sizeof(Elysium::Core::Template::System::int32_t) * TotalNumberOfElements, 1, false, false);
			Elysium::Core::Template::Memory::Scoped::Arena ArenaAllocator = Elysium::Core::Template::Memory::Scoped::Arena(Options);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// pop a single element (to ensure nothing happens)
			ArenaAllocator.Pop<Elysium::Core::Template::System::int32_t>();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// reset the arena
			ArenaAllocator.Reset();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// push no elements
			Elysium::Core::Template::System::int32_t* AllocatedInstance0 = ArenaAllocator.Push<Elysium::Core::Template::System::int32_t>(0);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());
			Assert::IsNull(AllocatedInstance0);

			// push a single element
			Elysium::Core::Template::System::int32_t* AllocatedInstance1 = ArenaAllocator.Push<Elysium::Core::Template::System::int32_t>();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(4_ui64, ArenaAllocator.GetSize());
			Assert::IsNotNull(AllocatedInstance1);
			Assert::AreEqual(0, *AllocatedInstance1);
			*AllocatedInstance1 = 2;
			Assert::AreEqual(2, *AllocatedInstance1);

			// push an array of elements
			int* AllocatedInstances0 = ArenaAllocator.Push<Elysium::Core::Template::System::int32_t>(10);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(44_ui64, ArenaAllocator.GetSize());
			for (Elysium::Core::Template::System::uint8_t i = 0; i < 10; i++)
			{
				AllocatedInstances0[i] = i + 3;
			}
			Assert::IsNotNull(AllocatedInstances0);

			// pop no elements
			ArenaAllocator.Pop<Elysium::Core::Template::System::int32_t>(0);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(44_ui64, ArenaAllocator.GetSize());

			// pop more elements than the arena holds
			ArenaAllocator.Pop<Elysium::Core::Template::System::int32_t>(TotalNumberOfElements - 1);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(44_ui64, ArenaAllocator.GetSize());

			// pop a single element
			ArenaAllocator.Pop<Elysium::Core::Template::System::int32_t>();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(40_ui64, ArenaAllocator.GetSize());

			// pop a single element of twice the size
			ArenaAllocator.Pop<Elysium::Core::Template::System::int64_t>();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(32_ui64, ArenaAllocator.GetSize());

			// push more elements than the arena can hold (forcing "resize")
			Elysium::Core::Template::System::int32_t* AllocatedInstances1 = ArenaAllocator.Push<Elysium::Core::Template::System::int32_t>(
				TotalNumberOfElements + 1);
			Assert::AreEqual(2_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(164_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(164_ui64, ArenaAllocator.GetSize());
			Assert::IsNotNull(AllocatedInstances1);

			// clear the arena
			ArenaAllocator.Clear();
			Assert::AreEqual(2_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(164_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// reset the arena again
			ArenaAllocator.Reset();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(84_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());
		}

		TEST_METHOD(TrivialStructsOnly)
		{
			constexpr const Elysium::Core::Template::System::size TotalNumberOfElements = 20;

			constexpr Elysium::Core::Template::Memory::Scoped::ArenaOptions Options = Elysium::Core::Template::Memory::Scoped::ArenaOptions(
				sizeof(TrivialStruct) * TotalNumberOfElements, 1, false, false);
			Elysium::Core::Template::Memory::Scoped::Arena ArenaAllocator = Elysium::Core::Template::Memory::Scoped::Arena(Options);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// pop a single element (to ensure nothing happens)
			ArenaAllocator.Pop<TrivialStruct>();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// reset the arena
			ArenaAllocator.Reset();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// push no elements
			TrivialStruct* AllocatedInstance0 = ArenaAllocator.Push<TrivialStruct>(0);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());
			Assert::IsNull(AllocatedInstance0);

			// push a single element
			TrivialStruct* AllocatedInstance1 = ArenaAllocator.Push<TrivialStruct>();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(8_ui64, ArenaAllocator.GetSize());
			Assert::IsNotNull(AllocatedInstance1);
			Assert::AreEqual(0, AllocatedInstance1->_SomeInt);
			AllocatedInstance1->_SomeInt = 2;
			Assert::AreEqual(2, AllocatedInstance1->_SomeInt);

			// push an array of elements
			TrivialStruct* AllocatedInstances0 = ArenaAllocator.Push<TrivialStruct>(10);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(88_ui64, ArenaAllocator.GetSize());
			for (Elysium::Core::Template::System::uint8_t i = 0; i < 10; i++)
			{
				AllocatedInstances0[i]._SomeInt = i + 3;
			}
			Assert::IsNotNull(AllocatedInstances0);

			// pop no elements
			ArenaAllocator.Pop<TrivialStruct>(0);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(88_ui64, ArenaAllocator.GetSize());

			// pop more elements than the arena holds
			ArenaAllocator.Pop<TrivialStruct>(TotalNumberOfElements - 1);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(88_ui64, ArenaAllocator.GetSize());

			// pop a single element
			ArenaAllocator.Pop<TrivialStruct>();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(80_ui64, ArenaAllocator.GetSize());

			// pop a single element of twice the size (faked by popping two elements)
			ArenaAllocator.Pop<TrivialStruct>(2);
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(160_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(64_ui64, ArenaAllocator.GetSize());

			// push more elements than the arena can hold (forcing "resize")
			TrivialStruct* AllocatedInstances1 = ArenaAllocator.Push<TrivialStruct>(TotalNumberOfElements + 1);
			Assert::AreEqual(2_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(328_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(328_ui64, ArenaAllocator.GetSize());
			Assert::IsNotNull(AllocatedInstances1);

			// clear the arena
			ArenaAllocator.Clear();
			Assert::AreEqual(2_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(328_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());

			// reset the arena again
			ArenaAllocator.Reset();
			Assert::AreEqual(1_ui64, ArenaAllocator.GetNumberOfPages());
			Assert::AreEqual(168_ui64, ArenaAllocator.GetCapacity());
			Assert::AreEqual(0_ui64, ArenaAllocator.GetSize());
		}
	};
}
