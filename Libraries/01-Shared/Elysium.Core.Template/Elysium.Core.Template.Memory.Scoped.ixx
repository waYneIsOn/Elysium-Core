export module Elysium.Core.Template.Memory.Scoped;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define WIN32_LEAN_AND_MEAN
	//#include <Windows.h>;
	import <Windows.h>;
	#endif

	
#else
#error "unsupported os"
#endif

import <cassert>;

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA
#include "Memory/Scoped/Arena.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAOPTIONS
#include "Memory/Scoped/ArenaOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAPAGE
#include "Memory/Scoped/ArenaPage.hpp"
#endif
}
