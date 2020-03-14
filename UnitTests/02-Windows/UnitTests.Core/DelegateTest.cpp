#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../../../Libraries/01-Shared/Elysium.Core/Delegate.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;

namespace UnitTests::Core
{
	float FreeOneParameter(int x)
	{
		return (float)x;
	}

	struct UnitTestClass
	{
		static inline float StaticOneParameter(int x)
		{
			return (float)x * x * x;
		}

		static inline double StaticTwoParameters(int x, int y)
		{
			return (double)x / y;
		}

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
		TEST_METHOD(Constructors)
		{
			Delegate<float, int> DelegateFree = Delegate<float, int>::CreateDelegate<&FreeOneParameter>();
			float ResultFree = DelegateFree(3);
			Assert::AreEqual(3.0f, ResultFree);

			Delegate<float, int> DelegateStatic = Delegate<float, int>::CreateDelegate<&UnitTestClass::StaticOneParameter>();
			float ResultStatic = DelegateStatic(2);
			Assert::AreEqual(8.0f, ResultStatic);

			Delegate<double, int, int> DelegateStatic2 = Delegate<double, int, int>::CreateDelegate<&UnitTestClass::StaticTwoParameters>();
			double ResultStatic2 = DelegateStatic2(5, 2);
			Assert::AreEqual(2.5, ResultStatic2);

			Delegate<float, int> DelegateLambda = Delegate<float, int>::CreateDelegate<[](int x) -> float { return (float)x * x; }>();
			float ResultLambda = DelegateLambda(3);
			Assert::AreEqual(9.0f, ResultLambda);

			UnitTestClass TestInstance = UnitTestClass();
			Delegate<float, int> DelegateInstance = Delegate<float, int>::CreateDelegate<UnitTestClass, &UnitTestClass::OneParameter>(TestInstance);
			float ResultInstance = DelegateInstance(5);
			Assert::AreEqual(25.0f, ResultInstance);
			
			Delegate<double, int, int> DelegateInstance2 = Delegate<double, int, int>::CreateDelegate<UnitTestClass, &UnitTestClass::TwoParameters>(TestInstance);
			double ResultInstance2 = DelegateInstance2(5, 2);
			Assert::AreEqual(2.5, ResultInstance2);
		}
	};
}
