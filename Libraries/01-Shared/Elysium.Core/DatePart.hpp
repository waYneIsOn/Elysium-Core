/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATEPART
#define ELYSIUM_CORE_DATEPART

namespace Elysium::Core
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class DatePart : long
#elif defined(__ANDROID__)
	enum class DatePart
#else
#error "undefined os"
#endif
	{
		Year = 0,
		DayOfYear = 1,
		Month = 2,
		Day = 3
	};
}
#endif
