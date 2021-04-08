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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Globalization
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class DigitShapes : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
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
