/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCMP
#define ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCMP

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
	inline Elysium::Core::Template::System::int32_t MemCmp(const void* Destination, const void* Source, Elysium::Core::Template::System::size Size)
	{	// @ToDo: stl remnant
		return std::memcmp(Destination, Source, Size);
	}
}
#endif
