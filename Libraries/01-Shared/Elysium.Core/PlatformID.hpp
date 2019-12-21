/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_PLATFORMID
#define ELYSIUM_CORE_PLATFORMID

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class PlatformID : uint32_t
#elif defined(__ANDROID__)
	enum class PlatformID
#else
#error "undefined os"
#endif
	{
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
