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

#ifndef _INC_TIME
#include <time.h>
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
    template <class Clock, class ClockDuration = Clock::Duration>
    class TimePoint
    {
	public:
		TimePoint() = delete;
		TimePoint(const ClockDuration& Duration);
		TimePoint(const TimePoint& Source) = delete;
		TimePoint(TimePoint&& Right) noexcept = delete;
		~TimePoint();

		TimePoint& operator=(const TimePoint& Source) = delete;
		TimePoint& operator=(TimePoint&& Right) noexcept = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const ClockDuration& GetTimeSinceEpoch() const;
    private:
		ClockDuration _Duration;
    };

	template<class Clock, class ClockDuration>
	inline TimePoint<Clock, ClockDuration>::TimePoint(const ClockDuration& Duration)
		: _Duration(Duration)
	{ }

	template<class Clock, class ClockDuration>
	inline TimePoint<Clock, ClockDuration>::~TimePoint()
	{ }

	template<class Clock, class ClockDuration>
	inline const ClockDuration& TimePoint<Clock, ClockDuration>::GetTimeSinceEpoch() const
	{
		return _Duration;
	}
}
#endif
