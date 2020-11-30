/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATETIMEKIND
#define ELYSIUM_CORE_DATETIMEKIND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
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