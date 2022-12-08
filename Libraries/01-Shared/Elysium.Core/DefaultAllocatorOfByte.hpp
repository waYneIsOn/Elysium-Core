/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFBYTE
#define ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFBYTE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Container
{
	//template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<Elysium::Core::byte>;

	using DefaultAllocatorOfByte = Elysium::Core::Template::Memory::DefaultAllocator<Elysium::Core::byte>;
}
#endif
