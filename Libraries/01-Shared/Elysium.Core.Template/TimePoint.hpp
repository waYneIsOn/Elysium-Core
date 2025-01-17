/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_TIMEPOINT
#define ELYSIUM_CORE_TEMPLATE_CHRONO_TIMEPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DURATION
#include "Duration.hpp"
#endif

namespace Elysium::Core::Template::Chrono
{
    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="Clock"></typeparam>
    /// <typeparam name="ClockDuration"></typeparam>
    template <class Clock, class ClockDuration = typename Clock::Duration>
    class TimePoint
    {
	public:
		constexpr TimePoint() = delete;

		constexpr TimePoint(const ClockDuration& Duration);

		constexpr TimePoint(const TimePoint& Source) = delete;

		constexpr TimePoint(TimePoint&& Right) noexcept = delete;

		constexpr ~TimePoint();
	public:
		constexpr TimePoint& operator=(const TimePoint& Source) = delete;

		constexpr TimePoint& operator=(TimePoint&& Right) noexcept = delete;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		constexpr const ClockDuration& GetTimeSinceEpoch() const;
    private:
		ClockDuration _Duration;
    };

	template<class Clock, class ClockDuration>
	inline constexpr TimePoint<Clock, ClockDuration>::TimePoint(const ClockDuration& Duration)
		: _Duration(Duration)
	{ }

	template<class Clock, class ClockDuration>
	inline constexpr TimePoint<Clock, ClockDuration>::~TimePoint()
	{ }

	template<class Clock, class ClockDuration>
	inline constexpr const ClockDuration& TimePoint<Clock, ClockDuration>::GetTimeSinceEpoch() const
	{
		return _Duration;
	}
}
#endif
