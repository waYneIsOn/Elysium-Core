#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/Delegate.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;

namespace UnitTests::Core
{
	float FreeOneParameter(int x)
	{
		return (float)x;
	}

	struct DelegateTestClass
	{
		static inline float StaticOneParameter(int x)
		{
			return (float)x * x * x;
		}

		static inline double StaticTwoParameters(int x, int y)
		{
			return (double)x / y;
		}

		static inline void StaticOneReferenceParameter(int & x)
		{ }

		static inline void StaticOnePointerParameter(int * x)
		{ }

		inline float OneParameter(int x)
		{
			return (float)x * x;
		}

		inline double TwoParameters(int x, int y)
		{
			return (double)x / y;
		}
	};

	TEST_CLASS(DelegateTests)
	{
	public:
		TEST_METHOD(BindDelegatesTest)
		{
			Delegate<float, int> DelegateFree = Delegate<float, int>::Bind<&FreeOneParameter>();
			float ResultFree = DelegateFree(3);
			Assert::AreEqual(3.0f, ResultFree);

			Delegate<float, int> DelegateStatic = Delegate<float, int>::Bind<&DelegateTestClass::StaticOneParameter>();
			float ResultStatic = DelegateStatic(2);
			Assert::AreEqual(8.0f, ResultStatic);

			Delegate<double, int, int> DelegateStatic2 = Delegate<double, int, int>::Bind<&DelegateTestClass::StaticTwoParameters>();
			double ResultStatic2 = DelegateStatic2(5, 2);
			Assert::AreEqual(2.5, ResultStatic2);

			Delegate<float, int> DelegateLambda = Delegate<float, int>::Bind<[](int x) -> float { return (float)x * x; }>();
			float ResultLambda = DelegateLambda(3);
			Assert::AreEqual(9.0f, ResultLambda);

			DelegateTestClass TestInstance = DelegateTestClass();
			Delegate<float, int> DelegateInstance = Delegate<float, int>::Bind<DelegateTestClass, &DelegateTestClass::OneParameter>(TestInstance);
			float ResultInstance = DelegateInstance(5);
			Assert::AreEqual(25.0f, ResultInstance);
			
			Delegate<double, int, int> DelegateInstance2 = Delegate<double, int, int>::Bind<DelegateTestClass, &DelegateTestClass::TwoParameters>(TestInstance);
			double ResultInstance2 = DelegateInstance2(5, 2);
			Assert::AreEqual(2.5, ResultInstance2);
			
			Delegate<void, int&> DelegateReference = Delegate<void, int&>::Bind<&DelegateTestClass::StaticOneReferenceParameter>();

			Delegate<void, int*> DelegatePointer = Delegate<void, int*>::Bind<&DelegateTestClass::StaticOnePointerParameter>();
		}
	};
}
