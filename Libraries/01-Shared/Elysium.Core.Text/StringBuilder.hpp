/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#define ELYSIUM_CORE_TEXT_STRINGBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFCHARACTER
#include "DefaultAllocatorOfCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Template/StringBuilder.hpp"
#endif

namespace Elysium::Core::Text
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBuilder<char>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBuilder<wchar_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBuilder<char8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBuilder<char16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBuilder<char32_t>;

	using StringBuilder = Elysium::Core::Template::Text::StringBuilder<char>;
	using WideStringBuilder = Elysium::Core::Template::Text::StringBuilder<wchar_t>;
	using Utf8StringBuilder = Elysium::Core::Template::Text::StringBuilder<char8_t>;
	using Utf16StringBuilder = Elysium::Core::Template::Text::StringBuilder<char16_t>;
	using Utf32StringBuilder = Elysium::Core::Template::Text::StringBuilder<char32_t>;
}
#endif
