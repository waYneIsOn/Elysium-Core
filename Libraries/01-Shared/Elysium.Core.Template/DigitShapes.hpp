/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_DIGITSHAPES
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_DIGITSHAPES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::Globalization
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class DigitShapes : System::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
