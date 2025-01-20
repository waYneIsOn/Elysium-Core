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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_ARCHTECTURE
#include "../Architecture.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
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
        using Duration = NanoSeconds;
        using Representation = Duration::RepresentationType;
        using Period = Duration::PeriodType;

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
        // https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency
        // states "The frequency of the performance counter is fixed at system boot and is consistent across all processors. 
        // Therefore, the frequency need only be queried upon application initialization, and the result can be cached."
        // Ergo caching the value in a static variable should be ok here
        // @ToDo: check whether this is actually correct and remove static if necessary!
        static const Elysium::Core::Template::System::int64_t PerformanceFrequency = GetPerformanceFrequency();

        const Elysium::Core::Template::System::int64_t PerformanceCounter = GetPerformanceCounter();

        /*
        * The following solution has been taken from the following issue
        * https://github.com/microsoft/STL/issues/3828
        * and it's current implementation taken and adopted from
        * https://github.com/microsoft/STL/blob/ab57910040a0ccd9fa36e22536f3fc25a8225ef3/stl/inc/__msvc_chrono.hpp
        * Copyright (c) Microsoft Corporation.
        * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
        */
        static constexpr const Elysium::Core::Template::System::int64_t TenMHz = 10'000'000;
        static constexpr const Elysium::Core::Template::System::int64_t TwentyFourMHz = 24'000'000;

#if defined ELYSIUM_CORE_ARCHITECTURE_ANY_X86
#define ELYSIUM_CORE_ARCHITECTURE_LIKELY_ARM
#define ELYSIUM_CORE_ARCHITECTURE_LIKELY_X86 ELYSIUM_CORE_PATH_LIKELY
#elif defined ELYSIUM_CORE_ARCHITECTURE_ANY_ARM
#define ELYSIUM_CORE_ARCHITECTURE_LIKELY_ARM ELYSIUM_CORE_PATH_LIKELY
#define ELYSIUM_CORE_ARCHITECTURE_LIKELY_X86
#else
#define ELYSIUM_CORE_ARCHITECTURE_LIKELY_ARM
#define ELYSIUM_CORE_ARCHITECTURE_LIKELY_X64
#endif
        if (PerformanceFrequency == TenMHz) ELYSIUM_CORE_ARCHITECTURE_LIKELY_X86
        { 
            static_assert(Period::Denominator % TenMHz == 0, "Elysium::Core::Template::Chrono::SteadyClock::Now(): should never fail.");
            constexpr long long Multiplier = Period::Denominator / TenMHz;
            return TimePoint(Duration(PerformanceCounter * Multiplier));
        }
        else if (PerformanceFrequency == TwentyFourMHz) ELYSIUM_CORE_ARCHITECTURE_LIKELY_ARM
        {
            const long long Whole = (PerformanceCounter / TwentyFourMHz) * Period::Denominator;
            const long long Part = (PerformanceCounter % TwentyFourMHz) * Period::Denominator / TwentyFourMHz;
            return TimePoint(Duration(Whole + Part));
        }
        else
        {
            const long long Whole = (PerformanceCounter / PerformanceFrequency) * Period::Denominator;
            const long long Part = (PerformanceCounter % PerformanceFrequency) * Period::Denominator / PerformanceFrequency;
            return TimePoint(Duration(Whole + Part));
        }
#undef ELYSIUM_CORE_ARCHITECTURE_LIKELY_ARM
#undef ELYSIUM_CORE_ARCHITECTURE_LIKELY_X86

#else
#error "unsupported os"
#endif
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
