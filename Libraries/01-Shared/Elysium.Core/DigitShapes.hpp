/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_DIGITSHAPES
#define ELYSIUM_CORE_GLOBALIZATION_DIGITSHAPES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
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
