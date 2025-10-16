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

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATEPART
#include "DatePart.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEKIND
#include "DateTimeKind.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO
#include "../Elysium.Core.Template/Chrono.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API DateTime
	{
	public:
		constexpr DateTime() = default;

		constexpr DateTime(const Elysium::Core::Template::System::int64_t Ticks) noexcept;
		
		constexpr DateTime(const Elysium::Core::Template::System::int64_t Ticks, const Elysium::Core::DateTimeKind Kind) noexcept;
		
		constexpr DateTime(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month,
			const Elysium::Core::Template::System::int32_t Day) noexcept;
		
		constexpr DateTime(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month,
			const Elysium::Core::Template::System::int32_t Day, const Elysium::Core::Template::System::int32_t Hour,
			const Elysium::Core::Template::System::int32_t Minute, const Elysium::Core::Template::System::int32_t Second) noexcept;
		
		constexpr DateTime(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month,
			const Elysium::Core::Template::System::int32_t Day, const Elysium::Core::Template::System::int32_t Hour, 
			const Elysium::Core::Template::System::int32_t Minute, const Elysium::Core::Template::System::int32_t Second, 
			const Elysium::Core::Template::System::int32_t Millisecond) noexcept;
		
		constexpr DateTime(const DateTime& Source) noexcept;

		constexpr DateTime(DateTime&& Right) noexcept;

		constexpr ~DateTime() = default;
	public:
		constexpr DateTime& operator=(const DateTime& Source) noexcept;

		constexpr DateTime& operator=(DateTime&& Right) noexcept;
	public:
		constexpr TimeSpan operator+(const DateTime& Other);

		constexpr TimeSpan operator-(const DateTime& Other);

		constexpr DateTime& operator+(const TimeSpan& Value);
	public:
		constexpr bool operator<(const DateTime& Other) const noexcept;

		constexpr bool operator<=(const DateTime& Other) const noexcept;
	public:
		static constexpr DateTime MaxValue() noexcept;

		static constexpr DateTime MinValue() noexcept;

		static DateTime Now() noexcept;

		static DateTime Today() noexcept;

		static DateTime UtcNow() noexcept;

		static constexpr const bool IsLeapYear(const Elysium::Core::Template::System::int32_t Year) noexcept;
	public:
		constexpr const Elysium::Core::DateTimeKind GetKind() const noexcept;

		constexpr const Elysium::Core::Template::System::int64_t GetTicks() const noexcept;

		//constexpr DateTime GetDate() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetDay() const noexcept;

		//DayOfWeek GetDayOfWeek() const noexcept;
		
		//constexpr const Elysium::Core::Template::System::int32_t GetDayOfYear() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetHour() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetMillisecond() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetMinute() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetMonth() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetSecond() const noexcept;

		//constexpr TimeSpan GetTimeOfDay() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetYear() const noexcept;
	private:
		static constexpr const Elysium::Core::int64_t DateToTicks(const Elysium::Core::Template::System::int32_t Year,
			const Elysium::Core::Template::System::int32_t Month, const Elysium::Core::Template::System::int32_t Day);

		static constexpr const Elysium::Core::int64_t TimeToTicks(const Elysium::Core::Template::System::int32_t Hour,
			const Elysium::Core::Template::System::int32_t Minute, const Elysium::Core::Template::System::int32_t Second);
	private:
		constexpr const Elysium::Core::Template::System::int32_t GetDatePart(const Elysium::Core::DatePart Part) const noexcept;
	private:
		Elysium::Core::Template::System::int64_t _Ticks;
		Elysium::Core::DateTimeKind _Kind;
	};

	inline constexpr Elysium::Core::DateTime::DateTime(const Elysium::Core::Template::System::int64_t Ticks) noexcept
		: _Ticks(Ticks), _Kind(DateTimeKind::Unspecified)
	{ }

	inline constexpr Elysium::Core::DateTime::DateTime(const Elysium::Core::Template::System::int64_t Ticks, const DateTimeKind Kind) noexcept
		: _Ticks(Ticks), _Kind(Kind)
	{ }

	inline constexpr Elysium::Core::DateTime::DateTime(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month, const Elysium::Core::Template::System::int32_t Day) noexcept
		: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day))
	{ }

	inline constexpr Elysium::Core::DateTime::DateTime(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month, const Elysium::Core::Template::System::int32_t Day, const Elysium::Core::Template::System::int32_t Hour, const Elysium::Core::Template::System::int32_t Minute, const Elysium::Core::Template::System::int32_t Second) noexcept
		: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day) + TimeToTicks(Hour, Minute, Second))
	{ }

	inline constexpr Elysium::Core::DateTime::DateTime(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month, const Elysium::Core::Template::System::int32_t Day, const Elysium::Core::Template::System::int32_t Hour, const Elysium::Core::Template::System::int32_t Minute, const Elysium::Core::Template::System::int32_t Second, const Elysium::Core::Template::System::int32_t Millisecond) noexcept
		: Elysium::Core::DateTime::DateTime(DateToTicks(Year, Month, Day) + TimeToTicks(Hour, Minute, Second) + Millisecond * DateTimeUtility::TicksPerMillisecond)
	{ }

	inline constexpr Elysium::Core::DateTime::DateTime(const DateTime& Source) noexcept
		: _Ticks(Source._Ticks), _Kind(Source._Kind)
	{ }

	inline constexpr Elysium::Core::DateTime::DateTime(DateTime&& Right) noexcept
		: _Ticks(0), _Kind(DateTimeKind::Unspecified)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	inline constexpr Elysium::Core::DateTime& Elysium::Core::DateTime::operator=(const DateTime& Source) noexcept
	{
		if (this != &Source)
		{
			_Ticks = Source._Ticks;
			_Kind = Source._Kind;
		}
		return *this;
	}

	inline constexpr Elysium::Core::DateTime& Elysium::Core::DateTime::operator=(DateTime&& Right) noexcept
	{
		if (this != &Right)
		{
			_Ticks = Elysium::Core::Template::Functional::Move(Right._Ticks);
			_Kind = Elysium::Core::Template::Functional::Move(Right._Kind);

			Right._Ticks = 0;
			Right._Kind = DateTimeKind::Unspecified;
		}
		return *this;
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::DateTime::operator+(const DateTime& Other)
	{
		return TimeSpan(_Ticks + Other._Ticks);
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::DateTime::operator-(const DateTime& Other)
	{
		return TimeSpan(_Ticks - Other._Ticks);
	}

	inline constexpr Elysium::Core::DateTime& Elysium::Core::DateTime::operator+(const TimeSpan& Value)
	{
		_Ticks += Value._Ticks;
		return *this;
	}

	inline constexpr bool Elysium::Core::DateTime::operator<(const DateTime& Other) const noexcept
	{
		// @ToDo: this assumes _Kind to be the same on both instances
		return _Ticks < Other._Ticks;
	}

	inline constexpr bool Elysium::Core::DateTime::operator<=(const DateTime& Other) const noexcept
	{
		// @ToDo: this assumes _Kind to be the same on both instances
		return _Ticks <= Other._Ticks;
	}

	inline constexpr Elysium::Core::DateTime Elysium::Core::DateTime::MaxValue() noexcept
	{
		return DateTime(DateTimeUtility::MaxTicks, DateTimeKind::Unspecified);
	}

	inline constexpr Elysium::Core::DateTime Elysium::Core::DateTime::MinValue() noexcept
	{
		return DateTime(DateTimeUtility::MinTicks, DateTimeKind::Unspecified);
	}

	inline Elysium::Core::DateTime Elysium::Core::DateTime::Now() noexcept
	{
		// @ToDo: get tick-difference between utc and local time and add it
		Elysium::Core::int64_t UtcTicks = Elysium::Core::Template::Chrono::SystemClock::Now().GetTimeSinceEpoch().GetCount() +
			DateTimeUtility::UnixFileTimeOffset;

		return DateTime(UtcTicks, DateTimeKind::Local);
	}

	inline Elysium::Core::DateTime Elysium::Core::DateTime::Today() noexcept
	{
		// @ToDo
		return DateTime();
	}

	inline Elysium::Core::DateTime Elysium::Core::DateTime::UtcNow() noexcept
	{
		return DateTime(Elysium::Core::Template::Chrono::SystemClock::Now().GetTimeSinceEpoch().GetCount() + DateTimeUtility::UnixFileTimeOffset,
			DateTimeKind::Utc);
	}

	inline constexpr const bool Elysium::Core::DateTime::IsLeapYear(const Elysium::Core::Template::System::int32_t Year) noexcept
	{
		if (Year >= 1 && Year <= 9999)
		{
			return Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0);
		}
		else
		{
			return false;
		}
	}

	inline constexpr const Elysium::Core::DateTimeKind Elysium::Core::DateTime::GetKind() const noexcept
	{
		return _Kind;
	}

	inline constexpr const Elysium::Core::Template::System::int64_t Elysium::Core::DateTime::GetTicks() const noexcept
	{
		return _Ticks;
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::DateTime::GetDay() const noexcept
	{
		return GetDatePart(DatePart::Day);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::DateTime::GetHour() const noexcept
	{
		return ((_Ticks / DateTimeUtility::TicksPerHour) % 24);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::DateTime::GetMillisecond() const noexcept
	{
		return ((_Ticks / DateTimeUtility::TicksPerMillisecond) % 1000);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::DateTime::GetMinute() const noexcept
	{
		return ((_Ticks / DateTimeUtility::TicksPerMinute) % 60);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::DateTime::GetMonth() const noexcept
	{
		return GetDatePart(DatePart::Month);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::DateTime::GetSecond() const noexcept
	{
		return ((_Ticks / DateTimeUtility::TicksPerSecond) % 60);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::DateTime::GetYear() const noexcept
	{
		return GetDatePart(DatePart::Year);
	}

	inline constexpr const Elysium::Core::int64_t Elysium::Core::DateTime::DateToTicks(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month, const Elysium::Core::Template::System::int32_t Day)
	{
		if (Year >= 1 && Year <= 9999 && Month >= 1 && Month <= 12)
		{
			const Elysium::Core::int32_t* Days = IsLeapYear(Year) ? DateTimeUtility::DaysToMonth366 : DateTimeUtility::DaysToMonth365;
			if (Day >= 1 && Day <= Days[Month] - Days[Month - 1])
			{
				const Elysium::Core::int32_t LastYear = Year - 1;
				const Elysium::Core::int32_t DayTicks = LastYear * 365 + LastYear / 4 - LastYear / 100 + LastYear / 400 + Days[Month - 1] + Day - 1;
				return DayTicks * DateTimeUtility::TicksPerDay;
			}
		}
		throw ArgumentOutOfRangeException();
	}

	inline constexpr const Elysium::Core::int64_t Elysium::Core::DateTime::TimeToTicks(const Elysium::Core::Template::System::int32_t Hour, const Elysium::Core::Template::System::int32_t Minute, const Elysium::Core::Template::System::int32_t Second)
	{
		if (Hour >= 0 && Hour <= 24 && Minute >= 0 && Minute < 60 && Second >= 0 && Second < 60)
		{
			int64_t TotalSeconds = (int64_t)Hour * 3600 + (int64_t)Minute * 60 + (int64_t)Second;
			if (TotalSeconds > DateTimeUtility::MaxSeconds || TotalSeconds < DateTimeUtility::MinSeconds)
			{
				throw ArgumentOutOfRangeException();
			}
			return TotalSeconds * DateTimeUtility::TicksPerSecond;
		}
		throw ArgumentOutOfRangeException();
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::DateTime::GetDatePart(const Elysium::Core::DatePart Part) const noexcept
	{
		Elysium::Core::Template::System::int32_t DaysSince_01_01_0001 =
			static_cast<Elysium::Core::Template::System::int32_t>(_Ticks / DateTimeUtility::TicksPerDay);
		Elysium::Core::Template::System::int32_t Year400 = DaysSince_01_01_0001 / DateTimeUtility::DaysPer400Years;
		DaysSince_01_01_0001 -= Year400 * DateTimeUtility::DaysPer400Years;
		Elysium::Core::Template::System::int32_t Year100 = DaysSince_01_01_0001 / DateTimeUtility::DaysPer100Years;
		if (Year100 == 4)
		{
			Year100 = 3;
		}
		DaysSince_01_01_0001 -= Year100 * DateTimeUtility::DaysPer100Years;
		Elysium::Core::Template::System::int32_t Year4 = DaysSince_01_01_0001 / DateTimeUtility::DaysPer4Years;
		DaysSince_01_01_0001 -= Year4 * DateTimeUtility::DaysPer4Years;
		Elysium::Core::Template::System::int32_t Year1 = DaysSince_01_01_0001 / DateTimeUtility::DaysPerYear;
		if (Year1 == 4)
		{
			Year1 = 3;
		}
		if (Part == DatePart::Year)
		{
			return Year400 * 400 + Year100 * 100 + Year4 * 4 + Year1 + 1;
		}

		DaysSince_01_01_0001 -= Year1 * DateTimeUtility::DaysPerYear;
		if (Part == DatePart::DayOfYear)
		{
			return DaysSince_01_01_0001 + 1;
		}

		const bool IsLeapYear = Year1 == 3 && (Year4 != 24 || Year100 == 3);
		const Elysium::Core::Template::System::int32_t* Days = IsLeapYear ? DateTimeUtility::DaysToMonth366 : DateTimeUtility::DaysToMonth365;
		Elysium::Core::Template::System::int32_t Month = (DaysSince_01_01_0001 >> 5) + 1;
		while (DaysSince_01_01_0001 >= Days[Month])
		{
			Month++;
		}
		if (Part == DatePart::Month)
		{
			return Month;
		}

		return DaysSince_01_01_0001 - Days[Month - 1] + 1;
	}
}
#endif
