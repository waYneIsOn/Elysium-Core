#include "CppUnitTest.h"

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "../../01-Shared/UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../../../Libraries/01-Shared/Elysium.Core/TimeSpan.hpp"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Elysium::Core;

namespace UnitTests::Core
{
	TEST_CLASS(TimespanTests)
	{
	public:
		TEST_METHOD(Constructors)
		{
			TimeSpan TS0 = TimeSpan(25000000000);
			Assert::AreEqual(40, TS0.GetSeconds());

			TimeSpan TSClone = TimeSpan(TS0);
			Assert::AreEqual(40, TSClone.GetSeconds());
		}

		TEST_METHOD(FromX)
		{
			TimeSpan TSTicks = TimeSpan::FromTicks(25000000000);
			Asserts(TSTicks, 0, 40, 41, 0, 0, 2500000, 2500, 41.666666666666664, 0.69444444444444442, 0.028935185185185185);
			/*
			TimeSpan TSSeconds = TimeSpan::FromSeconds(15);
			Asserts(TSSeconds, 15000, 15, 0, 0, 0, 15000, 15, 0.25, 0.0041666666666666666, 0.00017361111111111112);

			TimeSpan TSMinutes = TimeSpan::FromMinutes(1.5);
			Asserts(TSMinutes, 90000, 90, 1, 0, 0, 90000, 90, 1.5, 0.025000000000000001, 0.0010416666666666667);

			TimeSpan TSHours = TimeSpan::FromHours(3.75);
			Asserts(TSHours, 13500000, 13500, 225, 3, 0, 13500000, 13500, 225, 3.75, 0.15625);

			TimeSpan TSDays = TimeSpan::FromDays(27.25);
			Asserts(TSDays, 2354400000, 2354400, 39240, 654, 27, 2354400000, 2354400, 39240, 654, 27.25);

			TimeSpan Sum = TSMinutes + TSSeconds;
			Assert::AreEqual(105, Sum.GetSeconds());
			*/
		}

		TEST_METHOD(Operators)
		{
			TimeSpan TSSeconds = TimeSpan::FromSeconds(15);
			TimeSpan TSMinutes = TimeSpan::FromMinutes(1.5);

			TSSeconds += TSMinutes;
			AssertExtended::AreEqual((__int64)1050000000, TSSeconds.GetTicks());
			Assert::AreEqual(45, TSSeconds.GetSeconds());
			Assert::AreEqual(105.0, TSSeconds.GetTotalSeconds());

			TimeSpan Sum = TSSeconds + TSMinutes;
			AssertExtended::AreEqual((__int64)1950000000, Sum.GetTicks());
			Assert::AreEqual(15, Sum.GetSeconds());
			Assert::AreEqual(195.0, Sum.GetTotalSeconds());
		}
	private:
		void Asserts(TimeSpan& TimeSpan, int ExpectedMilliseconds, int ExpectedSeconds, int ExpectedMinutes, int ExpectedHours, int ExpectedDays,
			double ExpectedTotalMilliseconds, double ExpectedTotalSeconds, double ExpectedTotalMinutes, double ExpectedTotalHours, double ExpectedTotalDays)
		{
			Assert::AreEqual(ExpectedMilliseconds, TimeSpan.GetMilliseconds());
			Assert::AreEqual(ExpectedSeconds, TimeSpan.GetSeconds());
			Assert::AreEqual(ExpectedMinutes, TimeSpan.GetMinutes());
			Assert::AreEqual(ExpectedHours, TimeSpan.GetHours());
			Assert::AreEqual(ExpectedDays, TimeSpan.GetDays());

			Assert::AreEqual(ExpectedTotalMilliseconds, TimeSpan.GetTotalMilliseconds());
			Assert::AreEqual(ExpectedTotalSeconds, TimeSpan.GetTotalSeconds());
			Assert::AreEqual(ExpectedTotalMinutes, TimeSpan.GetTotalMinutes());
			Assert::AreEqual(ExpectedTotalHours, TimeSpan.GetTotalHours());
			Assert::AreEqual(ExpectedTotalDays, TimeSpan.GetTotalDays());
		}
	};
}
