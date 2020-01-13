/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATETIME
#define ELYSIUM_CORE_DATETIME

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef _STDINT_H
#include <cstdint>
#endif

#ifndef ELYSIUM_CORE_DATETIMEKIND
#include "DateTimeKind.hpp"
#endif

#ifndef ELYSIUM_CORE_DATEPART
#include "DatePart.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "TimeSpan.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API DateTime
	{
	public:
		DateTime(int64_t Ticks);
		DateTime(int64_t Ticks, DateTimeKind Kind);
		DateTime(int Year, int Month, int Day);
		DateTime(int Year, int Month, int Day, int Hour, int Minute, int Second);
		DateTime(int Year, int Month, int Day, int Hour, int Minute, int Second, int Millisecond);
		DateTime(const DateTime& Source);
		DateTime(DateTime&& Right) noexcept;
		~DateTime();

		DateTime& operator=(const DateTime& Source);
		DateTime& operator=(DateTime&& Right) noexcept;

		TimeSpan operator+(const DateTime& Other) noexcept;
		TimeSpan operator-(const DateTime& Other) noexcept;

		static DateTime MaxValue();
		static DateTime MinValue();
		static DateTime Now();
		static DateTime Today();
		static DateTime UtcNow();

		DateTimeKind const GetKind() const;
		int64_t const GetTicks() const;

		//void GetDate(DateTime* Value) const;
		void GetDay(int* Value) const;
		//void GetDayOfWeek(DayOfWeek* Value) const;
		//void GetDayOfYear(int* Value) const;
		void GetHour(int* Value) const;
		void GetMillisecond(int* Value) const;
		void GetMinute(int* Value) const;
		void GetMonth(int* Value) const;
		void GetSecond(int* Value) const;
		//void GetTimeOfDay(TimeSpan* Value) const;
		void GetYear(int* Value) const;

		const int GetDay() const;
		const int GetHour() const;
		const int GetMillisecond() const;
		const int GetMinute() const;
		const int GetMonth() const;
		const int GetSecond() const;
		const int GetYear() const;

		static bool IsLeapYear(int Year);
	private:
		int64_t _Ticks;
		DateTimeKind _Kind;

		// ...
		static int64_t DateToTicks(int Year, int Month, int Day);
		static int64_t TimeToTicks(int Hour, int Minute, int Second);

		// ...
		int GetDatePart(DatePart Part) const;
	};
}
#endif
