/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCHR
#define ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCHR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

extern "C" const void* __cdecl memchr(const void* Source, int LookupCharacter, size_t Size);

namespace Elysium::Core::Template::Memory
{
    inline const void* MemChr(const void* Source, int LookupCharacter, Elysium::Core::Template::System::size Size)
    {	// @ToDo: libc
        return memchr(Source, LookupCharacter, Size);
    }
}
#endif
