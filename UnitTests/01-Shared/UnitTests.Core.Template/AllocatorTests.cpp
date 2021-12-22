#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/DefaultAllocator.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Template/MAllocator.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Functional;
using namespace Elysium::Core::Template::Memory;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	class MyClass
	{
	public:
		MyClass() = delete;
		MyClass(void* Value)
			: _Value(Value)
		{ }
		~MyClass()
		{ }

		void* _Value;
	};

	TEST_CLASS(AllocatorTests)
	{
	public:
		TEST_METHOD(DefaultAllocatorWithoutDefaultConstructor)
		{
			DefaultAllocator<MyClass> Allocator;
			AllocatorWithoutDefaultConstructor(Allocator);
		}

		TEST_METHOD(MAllocatorWithoutDefaultConstructor)
		{
			MAllocator<MyClass> Allocator;
			AllocatorWithoutDefaultConstructor(Allocator);
		}
	private:
		template <class Allocator>
		void AllocatorWithoutDefaultConstructor(Allocator& AllocatorInstance)
		{
			void* Value = (void*)0x01;
			const Elysium::Core::size InstanceLength = 3;
			const Elysium::Core::size TotalLength = 5;

			MyClass* Instances = AllocatorInstance.Allocate(TotalLength);

			for (Elysium::Core::size i = 0; i < InstanceLength; i++)
			{
				Instances[i] = MyClass(Value);
			}

			for (Elysium::Core::size i = 0; i < InstanceLength; i++)
			{
				MyClass& CurrentInstance = Instances[i];
				Assert::AreEqual(Value, CurrentInstance._Value);
			}
			for (Elysium::Core::size i = InstanceLength; i < TotalLength; i++)
			{
				MyClass& CurrentInstance = Instances[i];
				Assert::AreNotEqual(Value, CurrentInstance._Value);
			}

			AllocatorInstance.Deallocate(Instances, InstanceLength);
		}
	};
}