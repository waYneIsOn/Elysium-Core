/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMMOVE
#define ELYSIUM_CORE_TEMPLATE_MEMORY_MEMMOVE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

extern "C" void* __cdecl memmove(void* Destination, const void* Source, size_t Size);

namespace Elysium::Core::Template::Memory
{
    inline constexpr void* MemMove(void* Destination, const void* Source, Elysium::Core::Template::System::size Size)
    {	// @ToDo: libc
        return memmove(Destination, Source, Size);
    }
}
#endif
