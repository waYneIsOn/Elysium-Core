/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET
#define ELYSIUM_CORE_TEMPLATE_MEMORY_MEMSET

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

extern "C" void* __cdecl memset(void* dest, int c, size_t count);

namespace Elysium::Core::Template::Memory
{
	inline void* MemSet(void* Destination, Elysium::Core::Template::System::int32_t Value, Elysium::Core::Template::System::size Size)
	{
		return memset(Destination, Value, Size);
	}
}
#endif
