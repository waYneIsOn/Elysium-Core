#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../../../Libraries/01-Shared/Elysium.Core/Delegate.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;

namespace UnitTestsCore
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

		inline float OneParameter(int x)
		{
			return (float)x * x;
		}
	};

	TEST_CLASS(Core_Delegate)
	{
	public:
		TEST_METHOD(Constructors)
		{
			Delegate<float, int> DelegateFree = Delegate<float, int>::CreateDelegate<&FreeOneParameter>();
			float Result1 = DelegateFree(3);
			Assert::AreEqual(3.0f, Result1);

			Delegate<float, int> DelegateStatic = Delegate<float, int>::CreateDelegate<&UnitTestClass::StaticOneParameter>();
			float Result2 = DelegateStatic(2);
			Assert::AreEqual(8.0f, Result2);

			UnitTestClass TestInstance = UnitTestClass();
			Delegate<float, int> DelegateInstance = Delegate<float, int>::CreateDelegate<UnitTestClass, &UnitTestClass::OneParameter>(&TestInstance);
			float Result3 = DelegateInstance(5);
			Assert::AreEqual(25.0f, Result3);
		}
	};
}
