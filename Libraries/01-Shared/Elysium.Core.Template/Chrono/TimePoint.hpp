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

		inline constexpr TimePoint(const ClockDuration& Duration)
			: _Duration(Duration)
		{ }

		constexpr TimePoint(const TimePoint& Source) = delete;

		constexpr TimePoint(TimePoint&& Right) noexcept = delete;

		constexpr ~TimePoint() = default;
	public:
		constexpr TimePoint& operator=(const TimePoint& Source) = delete;

		constexpr TimePoint& operator=(TimePoint&& Right) noexcept = delete;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline constexpr const ClockDuration& GetTimeSinceEpoch() const
		{
			return _Duration;
		}
    private:
		ClockDuration _Duration;
    };
}
#endif
