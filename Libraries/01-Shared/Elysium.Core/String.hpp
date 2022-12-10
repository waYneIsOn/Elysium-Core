/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_STRING
#define ELYSIUM_CORE_STRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFCHARACTER
#include "DefaultAllocatorOfCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Elysium.Core.Template/String.hpp"
#endif

namespace Elysium::Core
{
	template class ELYSIUM_CORE_API Template::Text::String<char, Template::Text::CharacterTraits<char>, Memory::DefaultAllocatorOfChar>;
	template class ELYSIUM_CORE_API Template::Text::String<char8_t, Template::Text::CharacterTraits<char8_t>, Memory::DefaultAllocatorOfUtf8Char>;
	template class ELYSIUM_CORE_API Template::Text::String<char16_t, Template::Text::CharacterTraits<char16_t>, Memory::DefaultAllocatorOfUtf16Char>;
	template class ELYSIUM_CORE_API Template::Text::String<char32_t, Template::Text::CharacterTraits<char32_t>, Memory::DefaultAllocatorOfUtf32Char>;
	template class ELYSIUM_CORE_API Core::Template::Text::String<wchar_t, Template::Text::CharacterTraits<wchar_t>, Memory::DefaultAllocatorOfWideChar>;
	
	using String = Template::Text::String<char, Template::Text::CharacterTraits<char>, Memory::DefaultAllocatorOfChar>;
	using Utf8String = Template::Text::String<char8_t, Template::Text::CharacterTraits<char8_t>, Memory::DefaultAllocatorOfUtf8Char>;
	using Utf16String = Template::Text::String<char16_t, Template::Text::CharacterTraits<char16_t>, Memory::DefaultAllocatorOfUtf16Char>;
	using Utf32String = Template::Text::String<char32_t, Template::Text::CharacterTraits<char32_t>, Memory::DefaultAllocatorOfUtf32Char>;
	using WideString = Template::Text::String<wchar_t, Template::Text::CharacterTraits<wchar_t>, Memory::DefaultAllocatorOfWideChar>;
}
#endif
