/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_LANGUAGESCOPE
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_LANGUAGESCOPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::Globalization::Internal
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class LanguageScope : System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class LanguageScope
#else
#error "undefined os"
#endif
	{
		Individual = 0,

		Collection = 1,

		Macrolanguage = 2
	};
}
#endif
