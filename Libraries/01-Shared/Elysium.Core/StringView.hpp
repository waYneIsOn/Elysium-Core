/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_STRINGVIEW
#define ELYSIUM_CORE_STRINGVIEW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../Elysium.Core.Template/StringView.hpp"
#endif

namespace Elysium::Core
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringView<char>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringView<wchar_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringView<char8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringView<char16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Text::StringView<char32_t>;
	
	using StringView = Elysium::Core::Template::Text::StringView<char>;
	using WideStringView = Elysium::Core::Template::Text::StringView<wchar_t>;
	using Utf8StringView = Elysium::Core::Template::Text::StringView<char8_t>;
	using Utf16StringView = Elysium::Core::Template::Text::StringView<char16_t>;
	using Utf32StringView = Elysium::Core::Template::Text::StringView<char32_t>;
}
#endif
