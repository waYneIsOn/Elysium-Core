#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIME
#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;

namespace UnitTests::Core
{
	TEST_CLASS(DateTimeTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			DateTime DT0 = DateTime(634755744000000000);
			DateTime DT1 = DateTime(2012, 06, 18);

			Assert::AreEqual(DT0.GetTicks(), DT1.GetTicks());
		}
		TEST_METHOD(FromX)
		{
			DateTime Max = DateTime::MaxValue();
			Assert::AreEqual(3155378975999999999, Max.GetTicks());

			DateTime Min = DateTime::MinValue();
			Assert::AreEqual(0LL, Min.GetTicks());
		}
		TEST_METHOD(Operators)
		{
			// no tests yet
		}
	};
}
