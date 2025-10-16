/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TIMESPAN
#define ELYSIUM_CORE_TIMESPAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIMEUTILITY
#include "DateTimeUtility.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

namespace Elysium::Core
{
	class DateTime;

	class ELYSIUM_CORE_API TimeSpan
	{
		friend class DateTime;
	public:
		constexpr TimeSpan() noexcept = default;

		constexpr TimeSpan(const Elysium::Core::Template::System::int64_t Ticks) noexcept;

		constexpr TimeSpan(const Elysium::Core::Template::System::int32_t Hours, const Elysium::Core::Template::System::int32_t Minutes, const Elysium::Core::Template::System::int32_t Seconds);

		constexpr TimeSpan(const Elysium::Core::Template::System::int32_t Hours, const Elysium::Core::Template::System::int32_t Minutes, const Elysium::Core::Template::System::int32_t Seconds,
			const Elysium::Core::Template::System::int32_t Milliseconds);

		constexpr TimeSpan(const TimeSpan& Source) noexcept;

		constexpr TimeSpan(TimeSpan&& Right) noexcept;

		constexpr ~TimeSpan() noexcept = default;
	public:
		constexpr TimeSpan& operator=(const TimeSpan& Source) noexcept;

		constexpr TimeSpan& operator=(TimeSpan&& Right) noexcept;
	public:
		constexpr TimeSpan operator+(const TimeSpan& Other) const;

		constexpr TimeSpan operator-(const TimeSpan& Other) const;
	public:
		constexpr TimeSpan& operator+=(const TimeSpan& Other);
	public:
		static constexpr TimeSpan Zero() noexcept;

		static constexpr TimeSpan FromDays(double Value) noexcept;

		static constexpr TimeSpan FromHours(double Value) noexcept;

		static constexpr TimeSpan FromMinutes(double Value) noexcept;

		static constexpr TimeSpan FromSeconds(double Value) noexcept;

		static constexpr TimeSpan FromTicks(Elysium::Core::Template::System::int64_t Value) noexcept;
	public:
		constexpr const Elysium::Core::Template::System::int64_t GetTicks() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetDays() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetHours() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetMinutes() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetSeconds() const noexcept;

		constexpr const Elysium::Core::Template::System::int32_t GetMilliseconds() const noexcept;

		constexpr const double GetTotalDays() const noexcept;

		constexpr const double GetTotalHours() const noexcept;

		constexpr const double GetTotalMinutes() const noexcept;

		constexpr const double GetTotalSeconds() const noexcept;

		constexpr const double GetTotalMilliseconds() const noexcept;
	private:
		static constexpr TimeSpan Interval(double Value, Elysium::Core::Template::System::int32_t Scale) noexcept;
	private:
		Elysium::Core::Template::System::int64_t _Ticks;
	};

	inline constexpr Elysium::Core::TimeSpan::TimeSpan(const Elysium::Core::Template::System::int64_t Ticks) noexcept
		: _Ticks(Ticks)
	{ }

	inline constexpr Elysium::Core::TimeSpan::TimeSpan(const Elysium::Core::Template::System::int32_t Hours, const Elysium::Core::Template::System::int32_t Minutes, const Elysium::Core::Template::System::int32_t Seconds)
		: _Ticks((TimeSpan::FromHours(Hours) + TimeSpan::FromMinutes(Minutes) + TimeSpan::FromSeconds(Seconds)).GetTicks())
	{ }

	inline constexpr Elysium::Core::TimeSpan::TimeSpan(const Elysium::Core::Template::System::int32_t Hours, const Elysium::Core::Template::System::int32_t Minutes, const Elysium::Core::Template::System::int32_t Seconds, const Elysium::Core::Template::System::int32_t Milliseconds)
		: _Ticks((TimeSpan::FromHours(Hours) + TimeSpan::FromMinutes(Minutes) + TimeSpan::FromSeconds(Seconds) + TimeSpan::FromTicks(Milliseconds)).GetTicks())
	{ }

	inline constexpr Elysium::Core::TimeSpan::TimeSpan(const TimeSpan& Source) noexcept
		: _Ticks(Source._Ticks)
	{ }

	inline constexpr Elysium::Core::TimeSpan::TimeSpan(TimeSpan&& Right) noexcept
		: _Ticks(0)
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	inline constexpr Elysium::Core::TimeSpan& Elysium::Core::TimeSpan::operator=(const TimeSpan& Source) noexcept
	{
		if (this != &Source)
		{
			_Ticks = Source._Ticks;
		}
		return *this;
	}

	inline constexpr Elysium::Core::TimeSpan& Elysium::Core::TimeSpan::operator=(TimeSpan&& Right) noexcept
	{
		if (this != &Right)
		{
			_Ticks = Elysium::Core::Template::Functional::Move(Right._Ticks);
		}
		return *this;
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::operator+(const TimeSpan& Other) const
	{
		return TimeSpan(_Ticks + Other._Ticks);
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::operator-(const TimeSpan& Other) const
	{
		return TimeSpan(_Ticks - Other._Ticks);
	}

	inline constexpr Elysium::Core::TimeSpan& Elysium::Core::TimeSpan::operator+=(const TimeSpan& Other)
	{
		_Ticks += Other._Ticks;
		return *this;
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::Zero() noexcept
	{
		return TimeSpan(0);
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromDays(double Value) noexcept
	{
		return Interval(Value, DateTimeUtility::MillisecondsPerDay);
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromHours(double Value) noexcept
	{
		return Interval(Value, DateTimeUtility::MillisecondsPerHour);
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromMinutes(double Value) noexcept
	{
		return Interval(Value, DateTimeUtility::MillisecondsPerMinute);
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromSeconds(double Value) noexcept
	{
		return Interval(Value, DateTimeUtility::MillisecondsPerSecond);
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::FromTicks(Elysium::Core::Template::System::int64_t Value) noexcept
	{
		return TimeSpan(Value);
	}

	inline constexpr const Elysium::Core::Template::System::int64_t Elysium::Core::TimeSpan::GetTicks() const noexcept
	{
		return _Ticks;
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::TimeSpan::GetDays() const noexcept
	{
		return static_cast<Elysium::Core::int32_t>(_Ticks / DateTimeUtility::TicksPerDay);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::TimeSpan::GetHours() const noexcept
	{
		return static_cast<Elysium::Core::int32_t>((_Ticks / DateTimeUtility::TicksPerHour) % 24);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::TimeSpan::GetMinutes() const noexcept
	{
		return static_cast<Elysium::Core::int32_t>((_Ticks / DateTimeUtility::TicksPerMinute) % 60);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::TimeSpan::GetSeconds() const noexcept
	{
		return static_cast<Elysium::Core::int32_t>((_Ticks / DateTimeUtility::TicksPerSecond) % 60);
	}

	inline constexpr const Elysium::Core::Template::System::int32_t Elysium::Core::TimeSpan::GetMilliseconds() const noexcept
	{
		return static_cast<Elysium::Core::int32_t>((_Ticks / DateTimeUtility::TicksPerMillisecond) % 1000);
	}

	inline constexpr const double Elysium::Core::TimeSpan::GetTotalDays() const noexcept
	{
		return _Ticks * DateTimeUtility::DaysPerTick;
	}

	inline constexpr const double Elysium::Core::TimeSpan::GetTotalHours() const noexcept
	{
		return _Ticks * DateTimeUtility::HoursPerTick;
	}

	inline constexpr const double Elysium::Core::TimeSpan::GetTotalMinutes() const noexcept
	{
		return _Ticks * DateTimeUtility::MinutesPerTick;
	}

	inline constexpr const double Elysium::Core::TimeSpan::GetTotalSeconds() const noexcept
	{
		return _Ticks * DateTimeUtility::SecondsPerTick;
	}

	inline constexpr const double Elysium::Core::TimeSpan::GetTotalMilliseconds() const noexcept
	{
		double IntermediateValue = static_cast<double>(_Ticks * DateTimeUtility::MillisecondsPerTick);
		if (IntermediateValue > DateTimeUtility::MaxMilliseconds)
		{
			return static_cast<double>(DateTimeUtility::MaxMilliseconds);
		}
		else if (IntermediateValue < DateTimeUtility::MinMilliseconds)
		{
			return static_cast<double>(DateTimeUtility::MinMilliseconds);
		}
		else
		{
			return IntermediateValue;
		}
	}

	inline constexpr Elysium::Core::TimeSpan Elysium::Core::TimeSpan::Interval(double Value, Elysium::Core::Template::System::int32_t Scale) noexcept
	{
		double IntermediateValue = Value * Scale;
		double Milliseconds = IntermediateValue + (Value >= 0 ? 0.5 : -0.5);

		return TimeSpan(static_cast<Elysium::Core::int64_t>(Milliseconds) * DateTimeUtility::TicksPerMillisecond);
	}
}
#endif
