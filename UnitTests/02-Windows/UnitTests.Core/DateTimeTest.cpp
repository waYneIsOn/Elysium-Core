#include "CppUnitTest.h"

#include "CppUnitTestFrameworkExtension.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core/DateTime.hpp"

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

			AssertExtended::AreEqual(DT0.GetTicks(), DT1.GetTicks());
		}

		TEST_METHOD(FromX)
		{
			DateTime Max = DateTime::MaxValue();
			AssertExtended::AreEqual(3155378975999999999, Max.GetTicks());

			DateTime Min = DateTime::MinValue();
			AssertExtended::AreEqual(0LL, Min.GetTicks());
		}
	};
}
