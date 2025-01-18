/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_HIGHRESOLUTIONCLOCK
#define ELYSIUM_CORE_TEMPLATE_CHRONO_HIGHRESOLUTIONCLOCK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_STEADYCLOCK
#include "SteadyClock.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::Chrono
{
#ifdef ELYSIUM_CORE_OS_WINDOWS
    using HighResolutionClock = SteadyClock;
#else
    /*
    class HighResolutionClock final
    {
    public:
        using Representation = Elysium::Core::Template::System::int64_t;
        using Period = Numeric::Ratio<1, 1'000'000'000>; // 100 picoseconds

        using Duration = Duration<Representation, Period>;
        using TimePoint = TimePoint<HighResolutionClock>;
    public:
        constexpr HighResolutionClock() = delete;

        constexpr HighResolutionClock(const HighResolutionClock& Source) = delete;

        constexpr HighResolutionClock(HighResolutionClock&& Right) noexcept = delete;

        constexpr ~HighResolutionClock() = delete;
    public:
        constexpr HighResolutionClock& operator=(const HighResolutionClock& Source) = delete;

        constexpr HighResolutionClock& operator=(HighResolutionClock&& Right) noexcept = delete;
    public:
        inline static constexpr const bool IsSteady = true;
    public:
        static const TimePoint Now() noexcept;
    };

    inline const Elysium::Core::Template::Chrono::HighResolutionClock::TimePoint Elysium::Core::Template::Chrono::HighResolutionClock::Now() noexcept
    {
        return TimePoint(Duration(0));
    }
    */
#endif
}
#endif
