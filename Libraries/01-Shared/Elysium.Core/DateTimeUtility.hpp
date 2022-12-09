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
	public:
		DateTimeUtility& operator=(const DateTimeUtility& Source) = delete;

		DateTimeUtility& operator=(DateTimeUtility&& Right) noexcept = delete;
	public:
		// number of 100 nanosecond ticks per time unit 
		inline static constexpr const Elysium::Core::int64_t TicksPerMillisecond = 10000;
		inline static constexpr const Elysium::Core::int64_t TicksPerSecond = TicksPerMillisecond * 1000;
		inline static constexpr const Elysium::Core::int64_t TicksPerMinute = TicksPerSecond * 60;
		inline static constexpr const Elysium::Core::int64_t TicksPerHour = TicksPerMinute * 60;
		inline static constexpr const Elysium::Core::int64_t TicksPerDay = TicksPerHour * 24;

		// number of milliseconds per time unit 
		inline static constexpr const Elysium::Core::int32_t MillisecondsPerSecond = 1000;
		inline static constexpr const Elysium::Core::int32_t MillisecondsPerMinute = MillisecondsPerSecond * 60;
		inline static constexpr const Elysium::Core::int32_t MillisecondsPerHour = MillisecondsPerMinute * 60;
		inline static constexpr const Elysium::Core::int32_t MillisecondsPerDay = MillisecondsPerHour * 24;

		// days in specific years
		inline static constexpr const Elysium::Core::int32_t DaysPerYear = 365;
		inline static constexpr const Elysium::Core::int32_t DaysPerLeapYear = DaysPerYear + 1;
		inline static constexpr const Elysium::Core::int32_t DaysPer4Years = DaysPerYear * 4 + 1;
		inline static constexpr const Elysium::Core::int32_t DaysPer100Years = DaysPer4Years * 25 - 1;
		inline static constexpr const Elysium::Core::int32_t DaysPer400Years = DaysPer100Years * 4 + 1;

		// days from 01.01.0001 to 31.12.xxxx(x)
		inline static constexpr const Elysium::Core::int32_t DaysTo1601 = DaysPer400Years * 4;
		inline static constexpr const Elysium::Core::int32_t DaysTo1899 = DaysTo1601 + DaysPer100Years * 3 - 367;
		inline static constexpr const Elysium::Core::int32_t DaysTo10000 = DaysPer400Years * 25 - 366;

		// ...
		inline static constexpr const Elysium::Core::int64_t MinTicks = 0;
		inline static constexpr const Elysium::Core::int64_t MaxTicks = 3155378975999999999;	// DaysTo10000 * TicksPerDay - 1;
		inline static constexpr const Elysium::Core::int64_t MinMilliseconds = -922337203685477; // 9223372036854775808 / TicksPerMillisecond * -1;
		inline static constexpr const Elysium::Core::int64_t MaxMilliseconds = 922337203685477; // 9223372036854775807 / TicksPerMillisecond;

		inline static constexpr const Elysium::Core::int32_t DaysToMonth365[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
		inline static constexpr const Elysium::Core::int32_t DaysToMonth366[13] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

		// ...
		inline static constexpr const Elysium::Core::int64_t MinSeconds = -922337203685; // 9223372036854775808 / TicksPerSecond * -1;
		inline static constexpr const Elysium::Core::int64_t MaxSeconds = 922337203685; // 9223372036854775807 / TicksPerSecond;

		// ...
		inline static constexpr const double DaysPerTick = 1.0 / TicksPerDay;
		inline static constexpr const double HoursPerTick = 1.0 / TicksPerHour;
		inline static constexpr const double MinutesPerTick = 1.0 / TicksPerMinute;
		inline static constexpr const double SecondsPerTick = 1.0 / TicksPerSecond;
		inline static constexpr const double MillisecondsPerTick = 1.0 / TicksPerMillisecond;

		// ...
		inline static constexpr const Elysium::Core::int32_t DaysTo1970 = DaysPer400Years * 4 + DaysPer100Years * 3 + DaysPer4Years * 17 + DaysPerYear;
		inline static constexpr const Elysium::Core::int64_t UnixFileTimeOffset = DaysTo1970 * TicksPerDay;
	};
}
#endif
