/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFINTEGER
#define ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFINTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Memory
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<int8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<int16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<int32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<int64_t>;

	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<uint8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<uint16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<uint32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<uint64_t>;

	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<size>;
}
#endif
