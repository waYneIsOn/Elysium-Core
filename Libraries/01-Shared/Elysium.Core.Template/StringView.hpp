/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#define ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C>
	class StringViewBase
	{

	};

	using StringView = StringViewBase<char>;
	using WideStringView = StringViewBase<wchar_t>;
	using Utf8StringView = StringViewBase<char8_t>;
	using Utf16StringView = StringViewBase<char16_t>;
	using Utf32StringView = StringViewBase<char32_t>;
}
#endif
