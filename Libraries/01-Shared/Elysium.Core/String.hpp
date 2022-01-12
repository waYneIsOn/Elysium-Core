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

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOR
#include "DefaultAllocator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Elysium.Core.Template/String.hpp"
#endif

namespace Elysium::Core
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBase<char>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBase<wchar_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBase<char8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBase<char16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringBase<char32_t>;

	using String = Elysium::Core::Template::Text::StringBase<char>;
	using WideString = Elysium::Core::Template::Text::StringBase<wchar_t>;
	using Utf8String = Elysium::Core::Template::Text::StringBase<char8_t>;
	using Utf16String = Elysium::Core::Template::Text::StringBase<char16_t>;
	using Utf32String = Elysium::Core::Template::Text::StringBase<char32_t>;
}
#endif
