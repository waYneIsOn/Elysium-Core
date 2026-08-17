/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_TIMESPAN
#define ELYSIUM_CORE_TEMPLATE_CHRONO_TIMESPAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Chrono
{
	class DateTime;

	class TimeSpan
	{
	public:
		friend class DateTime;
	public:
		constexpr TimeSpan() noexcept = default;

		inline constexpr TimeSpan(const Elysium::Core::Template::System::int64_t Ticks) noexcept
			: _Ticks(Ticks)
		{ }

		inline constexpr TimeSpan(const Elysium::Core::Template::System::int32_t Hours, const Elysium::Core::Template::System::int32_t Minutes, 
			const Elysium::Core::Template::System::int32_t Seconds, const Elysium::Core::Template::System::int32_t Milliseconds = 0) 
			: _Ticks((FromHours(Hours) + FromMinutes(Minutes) + FromSeconds(Seconds) + FromTicks(Milliseconds)).GetTicks())
		{ }

		constexpr TimeSpan(const TimeSpan& Source) noexcept = default;

		constexpr TimeSpan(TimeSpan&& Right) noexcept = default;

		constexpr ~TimeSpan() noexcept = default;
	public:
		constexpr TimeSpan& operator=(const TimeSpan& Source) noexcept = default;

		constexpr TimeSpan& operator=(TimeSpan&& Right) noexcept = default;
	public:
		inline constexpr TimeSpan operator+(const TimeSpan& Other) const
		{
			return TimeSpan(_Ticks + Other._Ticks);
		}

		inline constexpr TimeSpan operator-(const TimeSpan& Other) const
		{
			return TimeSpan(_Ticks - Other._Ticks);
		}
	public:
		inline constexpr TimeSpan& operator+=(const TimeSpan& Other)
		{
			_Ticks += Other._Ticks;
			return *this;
		}
	public:
		inline static constexpr const TimeSpan Zero() noexcept
		{
			return 0;
		}
		
		inline static constexpr const TimeSpan FromDays(double Value) noexcept
		{
			return Interval(Value, Elysium::Core::Template::Chrono::DateTimeUtility::MillisecondsPerDay);
		}

		inline static constexpr const TimeSpan FromHours(double Value) noexcept
		{
			return Interval(Value, Elysium::Core::Template::Chrono::DateTimeUtility::MillisecondsPerHour);
		}

		inline static constexpr const TimeSpan FromMinutes(double Value) noexcept
		{
			return Interval(Value, Elysium::Core::Template::Chrono::DateTimeUtility::MillisecondsPerMinute);
		}

		inline static constexpr const TimeSpan FromSeconds(double Value) noexcept
		{
			return Interval(Value, Elysium::Core::Template::Chrono::DateTimeUtility::MillisecondsPerSecond);
		}

		inline static constexpr const TimeSpan FromTicks(Elysium::Core::Template::System::int64_t Value) noexcept
		{
			return Value;
		}
	public:
		inline constexpr const Elysium::Core::Template::System::int64_t GetTicks() const noexcept
		{
			return _Ticks;
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetDays() const noexcept
		{
			return static_cast<Elysium::Core::Template::System::int32_t>(_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerDay);
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetHours() const noexcept
		{
			return static_cast<Elysium::Core::Template::System::int32_t>((_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerHour) % 24);
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetMinutes() const noexcept
		{
			return static_cast<Elysium::Core::Template::System::int32_t>((_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerMinute) % 60);
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetSeconds() const noexcept
		{
			return static_cast<Elysium::Core::Template::System::int32_t>((_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerSecond) % 60);
		}

		inline constexpr const Elysium::Core::Template::System::int32_t GetMilliseconds() const noexcept
		{
			return static_cast<Elysium::Core::Template::System::int32_t>((_Ticks / Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerMillisecond) % 1000);
		}

		inline constexpr const double GetTotalDays() const noexcept
		{
			return _Ticks * Elysium::Core::Template::Chrono::DateTimeUtility::DaysPerTick;
		}

		inline constexpr const double GetTotalHours() const noexcept
		{
			return _Ticks * Elysium::Core::Template::Chrono::DateTimeUtility::HoursPerTick;
		}

		inline constexpr const double GetTotalMinutes() const noexcept
		{
			return _Ticks * Elysium::Core::Template::Chrono::DateTimeUtility::MinutesPerTick;
		}

		inline constexpr const double GetTotalSeconds() const noexcept
		{
			return _Ticks * Elysium::Core::Template::Chrono::DateTimeUtility::SecondsPerTick;
		}

		inline constexpr const double GetTotalMilliseconds() const noexcept
		{
			double IntermediateValue = static_cast<double>(_Ticks * Elysium::Core::Template::Chrono::DateTimeUtility::MillisecondsPerTick);
			if (IntermediateValue > Elysium::Core::Template::Chrono::DateTimeUtility::MaxMilliseconds)
			{
				return static_cast<double>(Elysium::Core::Template::Chrono::DateTimeUtility::MaxMilliseconds);
			}
			else if (IntermediateValue < Elysium::Core::Template::Chrono::DateTimeUtility::MinMilliseconds)
			{
				return static_cast<double>(Elysium::Core::Template::Chrono::DateTimeUtility::MinMilliseconds);
			}
			else
			{
				return IntermediateValue;
			}
		}
	private:
		inline static constexpr TimeSpan Interval(double Value, Elysium::Core::Template::System::int32_t Scale) noexcept
		{
			double IntermediateValue = Value * Scale;
			double Milliseconds = IntermediateValue + (Value >= 0 ? 0.5 : -0.5);

			return static_cast<Elysium::Core::Template::System::int64_t>(Milliseconds) * Elysium::Core::Template::Chrono::DateTimeUtility::TicksPerMillisecond;
		}
	private:
		Elysium::Core::Template::System::int64_t _Ticks;
	};
}
#endif
