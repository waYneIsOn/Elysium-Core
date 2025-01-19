/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_TEXTDIRECTION
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_TEXTDIRECTION

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
	enum class TextDirection : System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TextDirection
#else
#error "undefined os"
#endif
	{
		LeftToRight = 0,

		RightToLeft = 1,

		TopToBottom = 2,

		BottomToTop = 3,
	};
}
#endif
