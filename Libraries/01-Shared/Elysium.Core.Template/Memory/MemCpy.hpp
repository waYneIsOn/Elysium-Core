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

extern "C" void* __cdecl memcpy(void* Destination, const void* Source, size_t Size);

namespace Elysium::Core::Template::Memory
{
	inline void* MemCpy(void* Destination, const void* Source, Elysium::Core::Template::System::size Size)
	{	// @ToDo: libc
	    return memcpy(Destination, Source, Size);
        /*
        static constexpr const Elysium::Core::Template::System::uint8_t ChunkSize = 8;

        Elysium::Core::Template::System::size i = 0;

        // Copy in chunks while possible
        for (; i + ChunkSize <= Size; i += ChunkSize)
        {
            *(uint64_t*)((char*)Destination + i) = *(const uint64_t*)((const Elysium::Core::Template::System::byte*)Source + i);
        }

        // Copy any remaining bytes one by one
        for (; i < Size; ++i) 
        {
            ((Elysium::Core::Template::System::byte*)Destination)[i] = ((const Elysium::Core::Template::System::byte*)Source)[i];
        }

        return Destination;
        */
	}
}
#endif
