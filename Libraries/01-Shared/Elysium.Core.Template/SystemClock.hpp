/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_SYSTEMCLOCK
#define ELYSIUM_CORE_TEMPLATE_CHRONO_SYSTEMCLOCK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DURATION
#include "Duration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_TIMEPOINT
#include "TimePoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_RATIO
#include "Ratio.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)
#ifndef _TIME_H_
#include <time.h>
#endif
#else
#error "unsupported os"
#endif

namespace Elysium::Core::Template::Chrono
{
    /// <summary>
    /// Represents the operating system's clock tracking current time in utc-unix-time (ie. ticks since 01.01.1970)
    /// </summary>
    class SystemClock final
    {
    public:
        using Representation = long long;
        using Period = Numeric::Ratio<1, 10'000'000>; // 100 nanoseconds
        using Duration = Duration<Representation, Period>;
        using TimePoint = TimePoint<SystemClock>;
    public:
        SystemClock() = delete;
        SystemClock(const SystemClock& Source) = delete;
        SystemClock(SystemClock&& Right) noexcept = delete;
        ~SystemClock() = delete;

        SystemClock& operator=(const SystemClock& Source) = delete;
        SystemClock& operator=(SystemClock&& Right) noexcept = delete;
    public:
        inline static constexpr const bool IsSteady = false;

        inline static const TimePoint GetNow()
        {
#if defined(ELYSIUM_CORE_OS_WINDOWS)
            FILETIME FileTimeNow;
            GetSystemTimePreciseAsFileTime(&FileTimeNow);
            __int64 UnixTicks = ((__int64)FileTimeNow.dwLowDateTime + ((__int64)(FileTimeNow.dwHighDateTime) << 32LL)) -
                116444736000000000LL;   // as windows ticks start at 01.01.1601 we need to add this value to get to unix' 01.01.1970
#elif defined(ELYSIUM_CORE_OS_ANDROID)
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            __int64_t UnixTicks = now.tv_sec * 1000000000LL + now.tv_nsec;
#else
#error "unsupported os"
#endif
            return TimePoint(Duration(UnixTicks));
        }
    };
}
#endif
