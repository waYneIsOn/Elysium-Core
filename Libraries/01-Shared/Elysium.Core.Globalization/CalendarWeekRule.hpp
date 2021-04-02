/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_CALENDARWEEKRULE
#define ELYSIUM_CORE_GLOBALIZATION_CALENDARWEEKRULE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Globalization
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class CalendarWeekRule : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class CalendarWeekRule
#else
#error "undefined os"
#endif
	{
		FirstDay = 0,

		FirstFullWeek = 1,

		FirstFourDayWeek = 2,
	};
}
#endif
