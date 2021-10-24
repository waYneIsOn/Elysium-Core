/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_CALENDARALGORITHMTYPE
#define ELYSIUM_CORE_GLOBALIZATION_CALENDARALGORITHMTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core.Template/System.hpp"
#endif

namespace Elysium::Core::Globalization
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class CalendarAlgorithmType : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class CalendarAlgorithmType
#else
#error "undefined os"
#endif
	{
		Unknown = 0,

		SolarCalendar = 1,

		LunarCalendar = 2,

		LunisolarCalendar = 3,
	};
}
#endif
