/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_URIKIND
#define ELYSIUM_CORE_URIKIND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class UriKind : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class UriKind
#else
#error "undefined os"
#endif
	{
		RelativeOrAbsolute = 0,

		Absolute = 1,

		Relative = 2
	};
}
#endif
