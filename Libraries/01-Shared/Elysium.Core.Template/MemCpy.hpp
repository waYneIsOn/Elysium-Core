/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#define ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef _CSTRING_
#include <xstring>	// @ToDo: stl remnant
#endif

namespace Elysium::Core::Template::Memory
{
	inline void* MemCpy(void* Destination, const void* Source, Elysium::Core::Template::System::size Size)
	{	// @ToDo: stl remnant
		return std::memcpy(Destination, Source, Size);
	}
}
#endif
