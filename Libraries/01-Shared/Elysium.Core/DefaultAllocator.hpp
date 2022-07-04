/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOR
#define ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Memory
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<char>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<wchar_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<char8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<char16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<char32_t>;
}
#endif