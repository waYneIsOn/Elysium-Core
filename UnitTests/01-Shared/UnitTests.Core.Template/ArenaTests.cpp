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
			Elysium::Core::Template::Memory::Scoped::ArenaOptions Options = Elysium::Core::Template::Memory::Scoped::ArenaOptions(23, 1,
				false, false);
			Elysium::Core::Template::Memory::Scoped::Arena ArenaAllocator = Elysium::Core::Template::Memory::Scoped::Arena(Options);

			// assign more bytes at once than defined page-size
			void* AllocatedMemory0 = ArenaAllocator.Push(24);
			Assert::IsNotNull(AllocatedMemory0);
		}

		TEST_METHOD(ComplexTypeOnly)
		{
			Elysium::Core::Template::Memory::Scoped::ArenaOptions Options = Elysium::Core::Template::Memory::Scoped::ArenaOptions(
				sizeof(NonTrivialClass), 1,
				false, false);
			Elysium::Core::Template::Memory::Scoped::Arena ArenaAllocator = Elysium::Core::Template::Memory::Scoped::Arena(Options);

			// push a single element
			void* AllocatedMemory0 = ArenaAllocator.Push(sizeof(NonTrivialClass));
			NonTrivialClass* AllocatedInstance0 = ::new (AllocatedMemory0) NonTrivialClass();

			// push a single element (forcing "resize")
			void* AllocatedMemory1 = ArenaAllocator.Push(sizeof(NonTrivialClass));
			NonTrivialClass* AllocatedInstance1 = ::new (AllocatedMemory1) NonTrivialClass();


			bool bla = false;
		}

		TEST_METHOD(MixedTrivial)
		{
			Elysium::Core::Template::Memory::Scoped::ArenaOptions Options = Elysium::Core::Template::Memory::Scoped::ArenaOptions(80, 1,
				false, false);
			Elysium::Core::Template::Memory::Scoped::Arena ArenaAllocator = Elysium::Core::Template::Memory::Scoped::Arena(Options);

			Assert::Fail();
		}

		TEST_METHOD(IntegersOnly)
		{
			const Elysium::Core::Template::System::size TotalNumberOfElements = 20;

			Elysium::Core::Template::Memory::Scoped::ArenaOptions Options = Elysium::Core::Template::Memory::Scoped::ArenaOptions(
				sizeof(Elysium::Core::Template::System::int32_t) * TotalNumberOfElements, 1, false, false);
			Elysium::Core::Template::Memory::Scoped::Arena ArenaAllocator = Elysium::Core::Template::Memory::Scoped::Arena(Options);

			// pop a single element (to ensure nothing happens)
			ArenaAllocator.Pop<Elysium::Core::Template::System::int32_t>();
			Assert::AreEqual(0_ui64, ArenaAllocator.GetTotalSize());

			// push no elements
			Elysium::Core::Template::System::int32_t* AllocatedInstance0 = ArenaAllocator.Push<Elysium::Core::Template::System::int32_t>(0);
			Assert::AreEqual(0_ui64, ArenaAllocator.GetTotalSize());
			Assert::IsNull(AllocatedInstance0);

			// push more elements than the arena can hold
			Elysium::Core::Template::System::int32_t* AllocatedInstance1 = ArenaAllocator.Push<Elysium::Core::Template::System::int32_t>(
				TotalNumberOfElements + 1);
			Assert::AreEqual(0_ui64, ArenaAllocator.GetTotalSize());
			Assert::IsNull(AllocatedInstance1);

			// push a single element
			Elysium::Core::Template::System::int32_t* AllocatedInstance2 = ArenaAllocator.Push<Elysium::Core::Template::System::int32_t>();
			Assert::AreEqual(4_ui64, ArenaAllocator.GetTotalSize());
			Assert::IsNotNull(AllocatedInstance2);
			Assert::AreEqual(0, *AllocatedInstance2);
			*AllocatedInstance2 = 2;
			Assert::AreEqual(2, *AllocatedInstance2);

			// push an array of elements
			int* AllocatedInstances0 = ArenaAllocator.Push<Elysium::Core::Template::System::int32_t>(10);
			Assert::AreEqual(44_ui64, ArenaAllocator.GetTotalSize());
			for (Elysium::Core::Template::System::uint8_t i = 0; i < 10; i++)
			{
				AllocatedInstances0[i] = i + 3;
			}
			Assert::IsNotNull(AllocatedInstances0);

			// pop no elements
			ArenaAllocator.Pop<Elysium::Core::Template::System::int32_t>(0);
			Assert::AreEqual(44_ui64, ArenaAllocator.GetTotalSize());

			// pop more elements than the arena holds
			ArenaAllocator.Pop<Elysium::Core::Template::System::int32_t>(TotalNumberOfElements - 1);
			Assert::AreEqual(44_ui64, ArenaAllocator.GetTotalSize());

			// pop a single element
			ArenaAllocator.Pop<Elysium::Core::Template::System::int32_t>();
			Assert::AreEqual(40_ui64, ArenaAllocator.GetTotalSize());

			// pop a single element of twice the size
			ArenaAllocator.Pop<Elysium::Core::Template::System::int64_t>();
			Assert::AreEqual(32_ui64, ArenaAllocator.GetTotalSize());
		}

		TEST_METHOD(TrivialStructsOnly)
		{
			const Elysium::Core::Template::System::size TotalNumberOfElements = 20;

			Elysium::Core::Template::Memory::Scoped::ArenaOptions Options = Elysium::Core::Template::Memory::Scoped::ArenaOptions(
				sizeof(TrivialStruct) * TotalNumberOfElements, 1, false, false);
			Elysium::Core::Template::Memory::Scoped::Arena ArenaAllocator = Elysium::Core::Template::Memory::Scoped::Arena(Options);

			// pop a single element (to ensure nothing happens)
			ArenaAllocator.Pop<TrivialStruct>();
			Assert::AreEqual(0_ui64, ArenaAllocator.GetTotalSize());

			// push no elements
			TrivialStruct* AllocatedInstance0 = ArenaAllocator.Push<TrivialStruct>(0);
			Assert::AreEqual(0_ui64, ArenaAllocator.GetTotalSize());
			Assert::IsNull(AllocatedInstance0);

			// push more elements than the arena can hold
			TrivialStruct* AllocatedInstance1 = ArenaAllocator.Push<TrivialStruct>(TotalNumberOfElements + 1);
			Assert::AreEqual(0_ui64, ArenaAllocator.GetTotalSize());
			Assert::IsNull(AllocatedInstance1);

			// push a single element
			TrivialStruct* AllocatedInstance2 = ArenaAllocator.Push<TrivialStruct>();
			Assert::AreEqual(8_ui64, ArenaAllocator.GetTotalSize());
			Assert::IsNotNull(AllocatedInstance2);
			Assert::AreEqual(0, AllocatedInstance2->_SomeInt);
			AllocatedInstance2->_SomeInt = 2;
			Assert::AreEqual(2, AllocatedInstance2->_SomeInt);

			// push an array of elements
			TrivialStruct* AllocatedInstances0 = ArenaAllocator.Push<TrivialStruct>(10);
			Assert::AreEqual(88_ui64, ArenaAllocator.GetTotalSize());
			for (Elysium::Core::Template::System::uint8_t i = 0; i < 10; i++)
			{
				AllocatedInstances0[i]._SomeInt = i + 3;
			}
			Assert::IsNotNull(AllocatedInstances0);

			// pop no elements
			ArenaAllocator.Pop<TrivialStruct>(0);
			Assert::AreEqual(88_ui64, ArenaAllocator.GetTotalSize());

			// pop more elements than the arena holds
			ArenaAllocator.Pop<TrivialStruct>(TotalNumberOfElements - 1);
			Assert::AreEqual(88_ui64, ArenaAllocator.GetTotalSize());

			// pop a single element
			ArenaAllocator.Pop<TrivialStruct>();
			Assert::AreEqual(80_ui64, ArenaAllocator.GetTotalSize());

			// pop a single element of twice the size
			ArenaAllocator.Pop<TrivialStruct>(2);
			Assert::AreEqual(64_ui64, ArenaAllocator.GetTotalSize());
		}
	};
}
