#include "CppUnitTest.h"
#include "../UnitTestExtensions/CppUnitTestFrameworkExtension.hpp"

#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Chrono.hpp"
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/DateTime.hpp"

#include <chrono>

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Chrono;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests::Core::Template::Chrono
{
	TEST_CLASS(ClockTests)
	{
	public:
		TEST_METHOD(CompareSteadyClockToSTL)
		{
			const SteadyClock::TimePoint Now = SteadyClock::Now();
			const std::chrono::steady_clock::time_point STLNow = std::chrono::steady_clock::now();

			const SteadyClock::Duration& Duration = Now.GetTimeSinceEpoch();
			const std::chrono::steady_clock::duration STLDuration = STLNow.time_since_epoch();

			const SteadyClock::Representation Ticks = Duration.GetCount();
			const std::chrono::steady_clock::rep STLTick = STLDuration.count();

			// ...
			DateTime NowFromElysium = DateTime(Ticks);
			DateTime NowFromSTL = DateTime(STLTick);

			Assert::AreEqual(NowFromSTL.GetDay(), NowFromElysium.GetDay());
			Assert::AreEqual(NowFromSTL.GetMonth(), NowFromElysium.GetMonth());
			Assert::AreEqual(NowFromSTL.GetYear(), NowFromElysium.GetYear());

			Assert::AreEqual(NowFromSTL.GetHour(), NowFromElysium.GetHour());
			Assert::AreEqual(NowFromSTL.GetMinute(), NowFromElysium.GetMinute());
			Assert::AreEqual(NowFromSTL.GetSecond(), NowFromElysium.GetSecond());
		}

		TEST_METHOD(CompareSystemClockToSTL)
		{
			const SystemClock::TimePoint Now = SystemClock::Now();
			const std::chrono::system_clock::time_point STLNow = std::chrono::system_clock::now();

			const SystemClock::Duration& Duration = Now.GetTimeSinceEpoch();
			const std::chrono::system_clock::duration STLDuration = STLNow.time_since_epoch();

			const SystemClock::Representation Ticks = Duration.GetCount();
			const std::chrono::system_clock::rep STLTick = STLDuration.count();
			/*
			const SystemClock::Representation ReducedTicks = Ticks / 1000;
			const std::chrono::system_clock::rep ReducedSTLTick = STLTick / 1000;

			// This comparison might obviously still fail at certain points in time but is alright for now!
			Assert::AreEqual(ReducedTicks, ReducedSTLTick);
			*/
			// instead of comparing reduced ticks as seen above, use DateTime and compare day, month, year, hour, minute and second
			DateTime NowFromElysium = DateTime(Ticks);
			DateTime NowFromSTL = DateTime(STLTick);
			
			Assert::AreEqual(NowFromSTL.GetDay(), NowFromElysium.GetDay());
			Assert::AreEqual(NowFromSTL.GetMonth(), NowFromElysium.GetMonth());
			Assert::AreEqual(NowFromSTL.GetYear(), NowFromElysium.GetYear());

			Assert::AreEqual(NowFromSTL.GetHour(), NowFromElysium.GetHour());
			Assert::AreEqual(NowFromSTL.GetMinute(), NowFromElysium.GetMinute());
			Assert::AreEqual(NowFromSTL.GetSecond(), NowFromElysium.GetSecond());
		}
	};
}
