/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_STEADYCLOCK
#define ELYSIUM_CORE_TEMPLATE_CHRONO_STEADYCLOCK

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
#include "../Ratio.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
    #ifndef _PROFILEAPI_H_
    #include <profileapi.h>
    #endif
/*
    #ifndef _SYSINFOAPI_H_
    #include <sysinfoapi.h>
    #endif
*/
#else
#error "unsupported os"
#endif

namespace Elysium::Core::Template::Chrono
{
    class SteadyClock final
    {
    public:
        using Representation = Elysium::Core::Template::System::int64_t;
        using Period = Numeric::Ratio<1, 1'000'000'000>; // 100 picoseconds

        using Duration = Duration<Representation, Period>;
        using TimePoint = TimePoint<SteadyClock>;
    public:
        constexpr SteadyClock() = delete;

        constexpr SteadyClock(const SteadyClock& Source) = delete;

        constexpr SteadyClock(SteadyClock&& Right) noexcept = delete;

        constexpr ~SteadyClock() = delete;
    public:
        constexpr SteadyClock& operator=(const SteadyClock& Source) = delete;

        constexpr SteadyClock& operator=(SteadyClock&& Right) noexcept = delete;
    public:
        inline static constexpr const bool IsSteady = true;
    public:
        static const TimePoint Now() noexcept;
    private:
#if defined ELYSIUM_CORE_OS_WINDOWS
        static const Elysium::Core::Template::System::int64_t GetPerformanceFrequency() noexcept;

        static const Elysium::Core::Template::System::int64_t GetPerformanceCounter() noexcept;
#endif
    };

    inline const Elysium::Core::Template::Chrono::SteadyClock::TimePoint Elysium::Core::Template::Chrono::SteadyClock::Now() noexcept
    {
#if defined ELYSIUM_CORE_OS_WINDOWS
        // https://learn.microsoft.com/en-us/cpp/standard-library/steady-clock-struct?view=msvc-170

        // https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency
        // states "The frequency of the performance counter is fixed at system boot and is consistent across all processors. 
        // Therefore, the frequency need only be queried upon application initialization, and the result can be cached."
        // Ergo caching the value in a static variable should be ok here
        // @ToDo: check whether this is actually correct and remove static if necessary!
        static const Elysium::Core::Template::System::int64_t PerformanceFrequency = GetPerformanceFrequency();

        const Elysium::Core::Template::System::int64_t PerformanceCounter = GetPerformanceCounter();


#else
#error "unsupported os"
#endif

        // @ToDo
        return TimePoint(Duration(0));
    }

#if defined ELYSIUM_CORE_OS_WINDOWS
    inline const Elysium::Core::Template::System::int64_t SteadyClock::GetPerformanceFrequency() noexcept
    {
        LARGE_INTEGER PerformanceFrequency;
        BOOL PerformanceFrequencyResult = QueryPerformanceFrequency(&PerformanceFrequency);
        /*
        * https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency
        * states that on "systems that run win-xp or later, the function will always succeed".
        * Ergo there's no need to check whether PerformanceFrequencyResult is TRUE or not!
        */

        return PerformanceFrequency.QuadPart;
    }

    inline const Elysium::Core::Template::System::int64_t SteadyClock::GetPerformanceCounter() noexcept
    {
        LARGE_INTEGER PerformanceCount;
        BOOL PerformanceCountResult = QueryPerformanceCounter(&PerformanceCount);
        /*
        * https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter
        * states that on "systems that run win-xp or later, the function will always succeed".
        * Ergo there's no need to check whether PerformanceCountResult is TRUE or not!
        */

        return PerformanceCount.QuadPart;
    }
#endif
}
#endif
