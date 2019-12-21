/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_GLOBALIZATION_DIGITSHAPES
#define ELYSIUM_CORE_GLOBALIZATION_DIGITSHAPES

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Globalization
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class DigitShapes : uint32_t
#elif defined(__ANDROID__)
	enum class DigitShapes
#else
#error "undefined os"
#endif
	{
		Context = 0,
		None = 1,
		NativeNational = 2
	};
}
#endif
