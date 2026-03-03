export module Elysium.Core.Template.Chrono;

import <Windows.h>;

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DURATION
#include "Chrono/Duration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_HIGHRESOLUTIONCLOCK
#include "Chrono/HighResolutionClock.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_STEADYCLOCK
#include "Chrono/SteadyClock.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_SYSTEMCLOCK
#include "Chrono/SystemClock.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_TIMEPOINT
#include "Chrono/TimePoint.hpp"
#endif
}
