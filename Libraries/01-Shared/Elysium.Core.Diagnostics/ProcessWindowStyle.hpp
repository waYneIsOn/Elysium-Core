/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESSWINDOWSTYLE
#define ELYSIUM_CORE_DIAGNOSTICS_PROCESSWINDOWSTYLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core.Template/System.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class ProcessWindowStyle : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
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
