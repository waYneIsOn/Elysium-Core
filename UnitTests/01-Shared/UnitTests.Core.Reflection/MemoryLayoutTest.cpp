#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Delegate.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Reflection
{
	class SimpleClass
	{
	public:
		SimpleClass()
			: _X(24), _Y(435.45f), _Z(new int(45))
		{ }
		~SimpleClass()
		{
			delete _Z;
		}

		inline const static int _A = 23;

		inline static int _B = 123;
		inline static int _C = 5448;

		void DoNothing() {};

		const int Add(const int A, const int B) const
		{
			return A + B;
		}
	private:
		inline const static int _D = 23;

		inline static int _E = 123;

		int _X;
		float _Y;
		const int* _Z;
	};

	TEST_CLASS(MemoryLayoutTest)
	{
	public:
		TEST_METHOD(SimpleClassTest)
		{
			SimpleClass Instance = SimpleClass();
			void* InstanceAddress = &Instance;

			// instance fields - stack/heap segment
			int* Field_X = (int*)InstanceAddress;

			float* Field_Y = (float*)((Elysium::Core::byte*)InstanceAddress + sizeof(int));

			const int** Field_Z = (const int**)((Elysium::Core::byte*)Field_Y + sizeof(float));

			// static const fields
			auto Field_A = &SimpleClass::_A;
			//auto Field_D = Field_A + sizeof(int);

			// static fields - data segment
			auto Field_B = &SimpleClass::_B;
			auto Field_C = &SimpleClass::_C;
			//auto Field_E = Field_C + sizeof(int);

			// methods - text segment
			void (SimpleClass:: * Method_DoNothing)() = &SimpleClass::DoNothing;
			const int (SimpleClass:: * Method_Add)(const int A, const int B) const = &SimpleClass::Add;
			//const int Value = (Instance.*Method_Add)(25, 25);

			// constructors - text segment
			//auto Constructor_Default = &Elysium::Core::String::String;

			// destructor - text segment
			//auto Destructor = &Elysium::Core::String::~String;
		}

		TEST_METHOD(PurelyVirtualClassTest)
		{
			Assert::Fail();
		}

		TEST_METHOD(VirtualBaseClassTest)
		{
			Assert::Fail();
		}

		TEST_METHOD(VirtualDerivedClassTest)
		{
			Assert::Fail();
		}

		TEST_METHOD(TemplateClassTest)
		{
			Assert::Fail();
		}

		TEST_METHOD(StructTest)
		{
			Assert::Fail();
		}
	};
}
