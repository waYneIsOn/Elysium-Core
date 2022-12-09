/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_PLATFORMID
#define ELYSIUM_CORE_PLATFORMID

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class PlatformID : Template::System::int8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class PlatformID
#else
#error "undefined os"
#endif
	{
		Unknown = -1,

		/*
		//Win32S = 0,
		//Win32Windows = 1,
		Win32NT = 2,
		//WinCE = 3,
		Unix = 4,
		Xbox = 5,
		MacOSX = 6,
		*/

		// desktop os
		WindowsDesktop = 0,
		Linux = 1,	// unix => linux, ubuntu, macOS, ...
		MacOSX = 2,

		// server os
		WindowsServer = 3,

		// mobile os (tablet and phone)
		WindowsPhone = 4,
		WindowsCE = 5,
		Android = 6,
		iOS = 7,

		// console os
		OrbisOS = 8,	// playstation
		Switch = 9,
		Xbox = 10,
	};
}
#endif
