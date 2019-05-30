/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#define ELYSIUM_CORE_DATETIMEUTILITY

namespace Elysium
{
	namespace Core
	{
		class DateTimeUtility
		{
		public:
			// number of 100 nanosecond ticks per time unit 
			static const __int64 TicksPerMillisecond = 10000;
			static const __int64 TicksPerSecond = 10000000;		// TicksPerMillisecond * 1000;
			static const __int64 TicksPerMinute = 600000000;	// TicksPerSecond * 60;
			static const __int64 TicksPerHour = 36000000000;	// TicksPerMinute * 60;
			static const __int64 TicksPerDay = 864000000000;	// TicksPerHour * 24;

			// number of milliseconds per time unit 
			static const int MillisecondsPerSecond = 1000;
			static const int MillisecondsPerMinute = 60000;
			static const int MillisecondsPerHour = 3600000;
			static const int MillisecondsPerDay = 86400000;

			// days in specific years
			static const int DaysPerYear = 365;
			static const int DaysPerLeapYear = 366;		// DaysPerYear + 1
			static const int DaysPer4Years = 1461;		// DaysPerYear * 4 + 1
			static const int DaysPer100Years = 36524;	// DaysPer4Years * 25 - 1
			static const int DaysPer400Years = 146097;	// DaysPer100Years * 4 + 1

			// days from 01.01.0001 to 31.12.xxxx(x)
			static const int DaysTo1601 = 584388;	// DaysPer400Years * 4;
			static const int DaysTo1899 = 693593;	// DaysTo1601 + DaysPer100Years * 3 - 367;
			static const int DaysTo10000 = 3652059;	// DaysPer400Years * 25 - 366;

			// ...
			static const __int64 MinTicks = 0;
			static const __int64 MaxTicks = 3155378975999999999;	// DaysTo10000 * TicksPerDay - 1;
			static const __int64 MinMilliseconds = -922337203685477; // 9223372036854775808 / TicksPerMillisecond * -1;
			static const __int64 MaxMilliseconds = 922337203685477; // 9223372036854775807 / TicksPerMillisecond;

			static const int DaysToMonth365[13];
			static const int DaysToMonth366[13];

			// ...
			static const __int64 MinSeconds = -922337203685; // 9223372036854775808 / TicksPerSecond * -1;
			static const __int64 MaxSeconds = 922337203685; // 9223372036854775807 / TicksPerSecond;

			// ...
			static const double DaysPerTick;
			static const double HoursPerTick;
			static const double MinutesPerTick;
			static const double SecondsPerTick;
			static const double MillisecondsPerTick;
		private:
			DateTimeUtility();
			~DateTimeUtility();
		};
	}
}
#endif
