/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFSTRING
#define ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFSTRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFCHARACTER
#include "DefaultAllocatorOfCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Memory
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<String>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<Utf8String>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<Utf16String>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<Utf32String>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<WideString>;
	
	using DefaultAllocatorOfString = Elysium::Core::Template::Memory::DefaultAllocator<String>;
	using DefaultAllocatorOfUtf8String = Elysium::Core::Template::Memory::DefaultAllocator<Utf8String>;
	using DefaultAllocatorOfUtf16String = Elysium::Core::Template::Memory::DefaultAllocator<Utf16String>;
	using DefaultAllocatorOfUtf32String = Elysium::Core::Template::Memory::DefaultAllocator<Utf32String>;
	using DefaultAllocatorOfWideString = Elysium::Core::Template::Memory::DefaultAllocator<WideString>;
}
#endif
