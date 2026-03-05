/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSWINDOWSTYLE
#define ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESSWINDOWSTYLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Diagnostics
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ProcessWindowStyle : System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ProcessWindowStyle
#else
#error "undefined os"
#endif
	{
		Normal = 0,

		Hidden = 1,

		Minimized = 2,

		Maximized = 3,
	};
}
#endif
