/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATETIMEKIND
#define ELYSIUM_CORE_DATETIMEKIND

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class DateTimeKind : uint32_t
#elif defined(__ANDROID__)
	enum class DateTimeKind
#else
#error "undefined os"
#endif
	{
		// ...
		Unspecified = 0,

		// ...
		Utc = 1,

		// ...
		Local = 2
	};
}
#endif