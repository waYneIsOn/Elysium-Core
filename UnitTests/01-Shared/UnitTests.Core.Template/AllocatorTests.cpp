#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/DefaultAllocator.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/MAllocator.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Core::Template::Functional;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Container
{
	class MyClass
	{
	public:
		MyClass(void* Value)
			: _Value(Value)
		{ }
		~MyClass()
		{
			if (_Value != nullptr)
			{
				delete _Value;
				_Value = nullptr;
			}
		}

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
			void* Value = nullptr;
			const size_t InstanceLength = 3;
			const size_t TotalLength = 5;

			MyClass* Instances = AllocatorInstance.Allocate(TotalLength);

			for (size_t i = 0; i < InstanceLength; i++)
			{
				Instances[i] = MyClass(Value);
			}

			for (size_t i = 0; i < InstanceLength; i++)
			{
				MyClass& CurrentInstance = Instances[i];
				Assert::AreEqual(Value, CurrentInstance._Value);
			}
			for (size_t i = InstanceLength; i < TotalLength; i++)
			{
				MyClass& CurrentInstance = Instances[i];
				Assert::AreNotEqual(Value, CurrentInstance._Value);
			}

			AllocatorInstance.Deallocate(Instances, InstanceLength);
		}
	};
}