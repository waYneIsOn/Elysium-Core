/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATETIME
#define ELYSIUM_CORE_DATETIME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEKIND
#include "DateTimeKind.hpp"
#endif

#ifndef ELYSIUM_CORE_DATEPART
#include "DatePart.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "TimeSpan.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API DateTime
	{
	public:
		DateTime(Elysium::Core::int64_t Ticks);
		DateTime(Elysium::Core::int64_t Ticks, Elysium::Core::DateTimeKind Kind);
		DateTime(Elysium::Core::int32_t Year, Elysium::Core::int32_t Month, Elysium::Core::int32_t Day);
		DateTime(Elysium::Core::int32_t Year, Elysium::Core::int32_t Month, Elysium::Core::int32_t Day, Elysium::Core::int32_t Hour, Elysium::Core::int32_t Minute, Elysium::Core::int32_t Second);
		DateTime(Elysium::Core::int32_t Year, Elysium::Core::int32_t Month, Elysium::Core::int32_t Day, Elysium::Core::int32_t Hour, Elysium::Core::int32_t Minute, Elysium::Core::int32_t Second, Elysium::Core::int32_t Millisecond);
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

		const Elysium::Core::DateTimeKind GetKind() const;
		const Elysium::Core::int64_t GetTicks() const;

		//DateTime GetDate();
		const Elysium::Core::int32_t GetDay() const;
		//DayOfWeek GetDayOfWeek();
		//Elysium::Core::int32_t GetDayOfYear();
		const Elysium::Core::int32_t GetHour() const;
		const Elysium::Core::int32_t GetMillisecond() const;
		const Elysium::Core::int32_t GetMinute() const;
		const Elysium::Core::int32_t GetMonth() const;
		const Elysium::Core::int32_t GetSecond() const;
		//TimeSpan GetTimeOfDay();
		const Elysium::Core::int32_t GetYear() const;

		static const bool IsLeapYear(const Elysium::Core::int32_t Year);
	private:
		Elysium::Core::int64_t _Ticks;
		Elysium::Core::DateTimeKind _Kind;

		// ...
		static Elysium::Core::int64_t DateToTicks(const Elysium::Core::int32_t Year, const Elysium::Core::int32_t Month, const Elysium::Core::int32_t Day);
		static Elysium::Core::int64_t TimeToTicks(const Elysium::Core::int32_t Hour, const Elysium::Core::int32_t Minute, const Elysium::Core::int32_t Second);

		// ...
		const Elysium::Core::int32_t GetDatePart(const Elysium::Core::DatePart Part) const;
	};
}
#endif
