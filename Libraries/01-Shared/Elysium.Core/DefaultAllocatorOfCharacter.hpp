/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFCHARACTER
#define ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFCHARACTER

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
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<char8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<char16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<char32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<wchar_t>;
	
	using DefaultAllocatorOfChar = Elysium::Core::Template::Memory::DefaultAllocator<char>;
	using DefaultAllocatorOfUtf8Char = Elysium::Core::Template::Memory::DefaultAllocator<char8_t>;
	using DefaultAllocatorOfUtf16Char = Elysium::Core::Template::Memory::DefaultAllocator<char16_t>;
	using DefaultAllocatorOfUtf32Char = Elysium::Core::Template::Memory::DefaultAllocator<char32_t>;
	using DefaultAllocatorOfWideChar = Elysium::Core::Template::Memory::DefaultAllocator<wchar_t>;
}
#endif
