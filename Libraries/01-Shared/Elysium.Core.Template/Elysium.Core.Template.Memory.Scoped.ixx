module;

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
#error "unsupported os"
#endif

#ifndef _ASSERT_OK
#include <cassert>
#define _ASSERT_OK	// defined so Elysium::Core::Template::Memory::Scoped::Arena include works without warning C5244
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENA
#include "Memory/Scoped/Arena.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAOPTIONS
#include "Memory/Scoped/ArenaOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_SCOPED_ARENAPAGE
#include "Memory/Scoped/ArenaPage.hpp"
#endif

export module Elysium.Core.Template.Memory.Scoped;

export
{
	using Elysium::Core::Template::Memory::Scoped::Arena;
	using Elysium::Core::Template::Memory::Scoped::ArenaOptions;
	using Elysium::Core::Template::Memory::Scoped::ArenaPage;
}
