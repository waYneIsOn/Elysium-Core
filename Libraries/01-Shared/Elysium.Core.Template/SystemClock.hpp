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

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DURATION
#include "Duration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_TIMEPOINT
#include "TimePoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NUMERIC_RATIO
#include "Ratio.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
    #ifndef _SYSINFOAPI_H_
    #include <sysinfoapi.h>
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
        using Representation = Elysium::Core::Template::System::int64_t;
        using Period = Numeric::Ratio<1, 10'000'000>; // 100 nanoseconds
        using Duration = Duration<Representation, Period>;
        using TimePoint = TimePoint<SystemClock>;
    public:
        constexpr  SystemClock() = delete;

        constexpr SystemClock(const SystemClock& Source) = delete;

        constexpr SystemClock(SystemClock&& Right) noexcept = delete;

        constexpr ~SystemClock() = delete;
    public:
        constexpr SystemClock& operator=(const SystemClock& Source) = delete;

        constexpr SystemClock& operator=(SystemClock&& Right) noexcept = delete;
    public:
        inline static constexpr const bool IsSteady = false;
    public:
        static const TimePoint Now();
    };

    inline const Elysium::Core::Template::Chrono::SystemClock::TimePoint Elysium::Core::Template::Chrono::SystemClock::Now()
    {
#if defined ELYSIUM_CORE_OS_WINDOWS
        FILETIME FileTimeNow;
        GetSystemTimePreciseAsFileTime(&FileTimeNow);
        __int64 UnixTicks = (FileTimeNow.dwLowDateTime + ((FileTimeNow.dwHighDateTime) << 32LL)) -
            116444736000000000LL;   // as windows ticks start at 01.01.1601 we need to add this value to get to unix' 01.01.1970
        /*
#elif defined ELYSIUM_CORE_OS_ANDROID
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        __int64_t UnixTicks = now.tv_sec * 1000000000LL + now.tv_nsec;
        */
#else
#error "unsupported os"
#endif
        return TimePoint(Duration(UnixTicks));
    }
}
#endif
