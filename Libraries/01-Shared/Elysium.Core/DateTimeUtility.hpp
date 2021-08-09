/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#define ELYSIUM_CORE_DATETIMEUTILITY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core
{
	class DateTimeUtility
	{
	public:
		DateTimeUtility() = delete;
		DateTimeUtility(const DateTimeUtility& Source) = delete;
		DateTimeUtility(DateTimeUtility&& Right) noexcept = delete;
		~DateTimeUtility() = delete;

		DateTimeUtility& operator=(const DateTimeUtility& Source) = delete;
		DateTimeUtility& operator=(DateTimeUtility&& Right) noexcept = delete;

		// number of 100 nanosecond ticks per time unit 
		static const Elysium::Core::int64_t TicksPerMillisecond = 10000;
		static const Elysium::Core::int64_t TicksPerSecond = 10000000;		// TicksPerMillisecond * 1000;
		static const Elysium::Core::int64_t TicksPerMinute = 600000000;	// TicksPerSecond * 60;
		static const Elysium::Core::int64_t TicksPerHour = 36000000000;	// TicksPerMinute * 60;
		static const Elysium::Core::int64_t TicksPerDay = 864000000000;	// TicksPerHour * 24;

		// number of milliseconds per time unit 
		static const Elysium::Core::int32_t MillisecondsPerSecond = 1000;
		static const Elysium::Core::int32_t MillisecondsPerMinute = 60000;
		static const Elysium::Core::int32_t MillisecondsPerHour = 3600000;
		static const Elysium::Core::int32_t MillisecondsPerDay = 86400000;

		// days in specific years
		static const Elysium::Core::int32_t DaysPerYear = 365;
		static const Elysium::Core::int32_t DaysPerLeapYear = 366;		// DaysPerYear + 1
		static const Elysium::Core::int32_t DaysPer4Years = 1461;		// DaysPerYear * 4 + 1
		static const Elysium::Core::int32_t DaysPer100Years = 36524;	// DaysPer4Years * 25 - 1
		static const Elysium::Core::int32_t DaysPer400Years = 146097;	// DaysPer100Years * 4 + 1

		// days from 01.01.0001 to 31.12.xxxx(x)
		static const Elysium::Core::int32_t DaysTo1601 = 584388;	// DaysPer400Years * 4;
		static const Elysium::Core::int32_t DaysTo1899 = 693593;	// DaysTo1601 + DaysPer100Years * 3 - 367;
		static const Elysium::Core::int32_t DaysTo10000 = 3652059;	// DaysPer400Years * 25 - 366;

		// ...
		static const Elysium::Core::int64_t MinTicks = 0;
		static const Elysium::Core::int64_t MaxTicks = 3155378975999999999;	// DaysTo10000 * TicksPerDay - 1;
		static const Elysium::Core::int64_t MinMilliseconds = -922337203685477; // 9223372036854775808 / TicksPerMillisecond * -1;
		static const Elysium::Core::int64_t MaxMilliseconds = 922337203685477; // 9223372036854775807 / TicksPerMillisecond;

		inline static const Elysium::Core::int32_t DaysToMonth365[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
		inline static const Elysium::Core::int32_t DaysToMonth366[13] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

		// ...
		static const Elysium::Core::int64_t MinSeconds = -922337203685; // 9223372036854775808 / TicksPerSecond * -1;
		static const Elysium::Core::int64_t MaxSeconds = 922337203685; // 9223372036854775807 / TicksPerSecond;

		// ...
		inline static const double DaysPerTick = 1.0 / TicksPerDay;
		inline static const double HoursPerTick = 1.0 / TicksPerHour;
		inline static const double MinutesPerTick = 1.0 / TicksPerMinute;
		inline static const double SecondsPerTick = 1.0 / TicksPerSecond;
		inline static const double MillisecondsPerTick = 1.0 / TicksPerMillisecond;
	};
}
#endif
