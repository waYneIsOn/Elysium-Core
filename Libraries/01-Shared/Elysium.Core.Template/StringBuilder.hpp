/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGBUILDER
#define ELYSIUM_CORE_TEMPLATE_TEXT_STRINGBUILDER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLIST
#include "LinkedList.hpp"
#endif

namespace Elysium::Core::Template::Text
{
	template <Concepts::Character C>
	class StringBuilderBase
	{

	};

	using StringBuilder = StringBuilderBase<char>;
	using WideStringBuilder = StringBuilderBase<wchar_t>;
	using Utf8StringBuilder = StringBuilderBase<char8_t>;
	using Utf16StringBuilder = StringBuilderBase<char16_t>;
	using Utf32StringBuilder = StringBuilderBase<char32_t>;
}
#endif
