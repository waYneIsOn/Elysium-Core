/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATETIME
#define ELYSIUM_CORE_DATETIME

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEKIND
#include "DateTimeKind.hpp"
#endif

#ifndef ELYSIUM_CORE_DATEPART
#include "DatePart.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class EXPORT DateTime
		{
		public:
			DateTime(__int64 Ticks);
			DateTime(__int64 Ticks, DateTimeKind Kind);
			DateTime(int Year, int Month, int Day);
			DateTime(int Year, int Month, int Day, int Hour, int Minute, int Second);
			DateTime(int Year, int Month, int Day, int Hour, int Minute, int Second, int Millisecond);
			DateTime(const DateTime& Source);
			~DateTime();

			static DateTime MaxValue();
			static DateTime MinValue();
			static DateTime Now();
			static DateTime Today();
			static DateTime UtcNow();

			DateTimeKind const GetKind() const;
			__int64 const GetTicks() const;

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
			__int64 _Ticks;
			DateTimeKind _Kind;

			// ...
			static __int64 DateToTicks(int Year, int Month, int Day);
			static __int64 TimeToTicks(int Hour, int Minute, int Second);

			// ...
			int GetDatePart(DatePart Part) const;
		};
	}
}
#endif
