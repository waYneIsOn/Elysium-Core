/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIME
#define ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATEPART
#include "DatePart.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIMEKIND
#include "DateTimeKind.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_SYSTEMCLOCK
#include "SystemClock.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_TIMESPAN
#include "TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTOUTOFRANGEEXCEPTION
#include "../Exceptions/ArgumentOutOfRangeException.hpp"
#endif

namespace Elysium::Core::Template::Chrono
{
	class DateTime
	{
	public:
		constexpr DateTime() = default;

		inline constexpr DateTime(const Elysium::Core::Template::System::int64_t Ticks,
			const Elysium::Core::Template::Chrono::DateTimeKind Kind = Elysium::Core::Template::Chrono::DateTimeKind::Unspecified) noexcept
			: _Ticks(Ticks), _Kind(Kind)
		{ }

		constexpr DateTime(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month,
			const Elysium::Core::Template::System::int32_t Day, const Elysium::Core::Template::Chrono::DateTimeKind Kind = Elysium::Core::Template::Chrono::DateTimeKind::Unspecified) noexcept
			: _Ticks(DateToTicks(Year, Month, Day)), _Kind(Kind)
		{ }

		constexpr DateTime(const Elysium::Core::Template::System::int32_t Year, const Elysium::Core::Template::System::int32_t Month,
			const Elysium::Core::Template::System::int32_t Day, const Elysium::Core::Template::System::int32_t Hour,
			const Elysium::Core::Template::System::int32_t Minute, const Elysium::Core::Template::System::int32_t Second,
			const Elysium::Core::Template::System::int32_t Millisecond = 0,
			const Elysium::Core::Template::Chrono::DateTimeKind Kind = Elysium::Core::Template::Chrono::DateTimeKind::Unspecified) noexcept
			: _Ticks(DateToTicks(Year, Month, Day) + TimeToTicks(Hour, Minute, Second) + Millisecond * Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerMillisecond), _Kind(Kind)
		{ }

		constexpr DateTime(const DateTime& Source) noexcept = default;

		constexpr DateTime(DateTime&& Right) noexcept = default;

		constexpr ~DateTime() = default;
	public:
		constexpr DateTime& operator=(const DateTime& Source) noexcept = default;

		constexpr DateTime& operator=(DateTime&& Right) noexcept = default;
	public:
		inline constexpr TimeSpan operator+(const DateTime& Other)
		{
			return _Ticks + Other._Ticks;
		}

		inline constexpr TimeSpan operator-(const DateTime& Other)
		{
			return _Ticks - Other._Ticks;
		}

		inline constexpr DateTime& operator+(const TimeSpan& Value)
		{
			_Ticks += Value._Ticks;
			return *this;
		}
	public:
		inline constexpr bool operator<(const DateTime& Other) const noexcept
		{
			// @ToDo: this assumes _Kind to be the same on both instances
			return _Ticks < Other._Ticks;
		}

		inline constexpr bool operator<=(const DateTime& Other) const noexcept
		{
			// @ToDo: this assumes _Kind to be the same on both instances
			return _Ticks <= Other._Ticks;
		}
	public:
		inline static constexpr DateTime MaxValue() noexcept
		{
			return { Elysium::Core::Template::Chrono::DateTimeUtility::MaxTicks, Elysium::Core::Template::Chrono::DateTimeKind::Unspecified };
		}

		inline static constexpr DateTime MinValue() noexcept
		{
			return { Elysium::Core::Template::Chrono::DateTimeUtility::MinTicks, Elysium::Core::Template::Chrono::DateTimeKind::Unspecified };
		}

		inline static DateTime Now() noexcept
		{
			// @ToDo: get tick-difference between utc and local time and add it
			Elysium::Core::Template::System::int64_t UtcTicks = Elysium::Core::Template::Chrono::SystemClock::Now().GetTimeSinceEpoch().GetCount() +
				Elysium::Core::Template::Chrono::DateTimeUtility::UnixFileTimeOffset;

			return { UtcTicks, Elysium::Core::Template::Chrono::DateTimeKind::Local };
		}

		inline static DateTime Today() noexcept
		{
			// @ToDo
			throw;
		}

		inline static DateTime UtcNow() noexcept
		{
			Elysium::Core::Template::System::int64_t UtcTicks = Elysium::Core::Template::Chrono::SystemClock::Now().GetTimeSinceEpoch().GetCount() +
				Elysium::Core::Template::Chrono::DateTimeUtility::UnixFileTimeOffset;

			return { UtcTicks, Elysium::Core::Template::Chrono::DateTimeKind::Utc };
		}

		inline static constexpr const bool IsLeapYear(const Elysium::Core::Template::System::int32_t Year) noexcept
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
	public:
		inline constexpr const Elysium::Core::Template::Chrono::DateTimeKind GetKind() const noexcept
		{
			return _Kind;
		}

		inline constexpr const Elysium::Core::Template::System::int64_t GetTicks() const noexcept
		{
			return _Ticks;
		}

		//inline constexpr DateTime GetDate() const noexcept;

		inline constexpr const Elysium::Core::Template::System::int32_t GetDay() const noexcept
		{
			return GetDatePart(Elysium::Core::Template::Chrono::DatePart::Day);
		}

		//inline constexpr const DayOfWeek GetDayOfWeek() const noexcept;

		//inline constexpr const Elysium::Core::Template::System::int32_t GetDayOfYear() const noexcept;

		inline constexpr const Elysium::Core::Template::System::int32_t GetHour() const noexcept
		{
			return ((_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerHour) % 24);
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetMillisecond() const noexcept
		{
			return ((_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerMillisecond) % 1000);
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetMinute() const noexcept
		{
			return ((_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerMinute) % 60);
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetMonth() const noexcept
		{
			return GetDatePart(Elysium::Core::Template::Chrono::DatePart::Month);
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetSecond() const noexcept
		{
			return ((_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerSecond) % 60);
		}

		//inline constexpr TimeSpan GetTimeOfDay() const noexcept;

		inline constexpr const Elysium::Core::Template::System::int32_t GetYear() const noexcept
		{
			return GetDatePart(Elysium::Core::Template::Chrono::DatePart::Year);
		}
	private:
		inline static constexpr const Elysium::Core::Template::System::int64_t DateToTicks(const Elysium::Core::Template::System::int32_t Year,
			const Elysium::Core::Template::System::int32_t Month, const Elysium::Core::Template::System::int32_t Day)
		{
			if (Year >= 1 && Year <= 9999 && Month >= 1 && Month <= 12)
			{
				const Elysium::Core::Template::System::int32_t* Days = IsLeapYear(Year) ? DateTimeUtility::DaysToMonth366 : DateTimeUtility::DaysToMonth365;
				if (Day >= 1 && Day <= Days[Month] - Days[Month - 1])
				{
					const Elysium::Core::Template::System::int32_t LastYear = Year - 1;
					const Elysium::Core::Template::System::int32_t DayTicks = LastYear * 365 + LastYear / 4 - LastYear / 100 + LastYear / 400 + Days[Month - 1] + Day - 1;
					return DayTicks * DateTimeUtility::TicksPerDay;
				}
			}
			throw Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException();
		}

		inline static constexpr const Elysium::Core::Template::System::int64_t TimeToTicks(const Elysium::Core::Template::System::int32_t Hour,
			const Elysium::Core::Template::System::int32_t Minute, const Elysium::Core::Template::System::int32_t Second)
		{
			if (Hour >= 0 && Hour <= 24 && Minute >= 0 && Minute < 60 && Second >= 0 && Second < 60)
			{
				Elysium::Core::Template::System::int64_t TotalSeconds = (Elysium::Core::Template::System::int64_t)Hour * 3600 +
					(Elysium::Core::Template::System::int64_t)Minute * 60 + (Elysium::Core::Template::System::int64_t)Second;
				if (TotalSeconds > DateTimeUtility::MaxSeconds || TotalSeconds < DateTimeUtility::MinSeconds)
				{
					throw Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException();
				}
				return TotalSeconds * DateTimeUtility::TicksPerSecond;
			}
			throw Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException();
		}
	private:
		inline constexpr const Elysium::Core::Template::System::int32_t GetDatePart(const Elysium::Core::Template::Chrono::DatePart Part) const noexcept
		{
			Elysium::Core::Template::System::int32_t DaysSince_01_01_0001 =
				static_cast<Elysium::Core::Template::System::int32_t>(_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerDay);
			Elysium::Core::Template::System::int32_t Year400 = DaysSince_01_01_0001 / Elysium::Core::Template::Chrono::DateTimeUtility::DaysPer400Years;
			DaysSince_01_01_0001 -= Year400 * Elysium::Core::Template::Chrono::DateTimeUtility::DaysPer400Years;
			Elysium::Core::Template::System::int32_t Year100 = DaysSince_01_01_0001 / Elysium::Core::Template::Chrono::DateTimeUtility::DaysPer100Years;
			if (Year100 == 4)
			{
				Year100 = 3;
			}
			DaysSince_01_01_0001 -= Year100 * Elysium::Core::Template::Chrono::DateTimeUtility::DaysPer100Years;
			Elysium::Core::Template::System::int32_t Year4 = DaysSince_01_01_0001 / Elysium::Core::Template::Chrono::DateTimeUtility::DaysPer4Years;
			DaysSince_01_01_0001 -= Year4 * Elysium::Core::Template::Chrono::DateTimeUtility::DaysPer4Years;
			Elysium::Core::Template::System::int32_t Year1 = DaysSince_01_01_0001 / Elysium::Core::Template::Chrono::DateTimeUtility::DaysPerYear;
			if (Year1 == 4)
			{
				Year1 = 3;
			}
			if (Part == Elysium::Core::Template::Chrono::DatePart::Year)
			{
				return Year400 * 400 + Year100 * 100 + Year4 * 4 + Year1 + 1;
			}

			DaysSince_01_01_0001 -= Year1 * Elysium::Core::Template::Chrono::DateTimeUtility::DaysPerYear;
			if (Part == Elysium::Core::Template::Chrono::DatePart::DayOfYear)
			{
				return DaysSince_01_01_0001 + 1;
			}

			const bool IsLeapYear = Year1 == 3 && (Year4 != 24 || Year100 == 3);
			const Elysium::Core::Template::System::int32_t* Days = IsLeapYear ?
				Elysium::Core::Template::Chrono::DateTimeUtility::DaysToMonth366 : Elysium::Core::Template::Chrono::DateTimeUtility::DaysToMonth365;
			Elysium::Core::Template::System::int32_t Month = (DaysSince_01_01_0001 >> 5) + 1;
			while (DaysSince_01_01_0001 >= Days[Month])
			{
				Month++;
			}
			if (Part == Elysium::Core::Template::Chrono::DatePart::Month)
			{
				return Month;
			}

			return DaysSince_01_01_0001 - Days[Month - 1] + 1;
		}
	private:
		Elysium::Core::Template::System::int64_t _Ticks;
		Elysium::Core::Template::Chrono::DateTimeKind _Kind;
	};
}
#endif
