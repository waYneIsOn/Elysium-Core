/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_STRING
#define ELYSIUM_CORE_STRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGBASE
#include "StringBase.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#pragma warning( disable : 4251 )

namespace Elysium::Core
{
	using Utf8Char = char;	// char8_t;

	using String = Collections::Template::StringBase<Utf8Char>;
	using WideString = Collections::Template::StringBase<wchar_t>;
}
#endif
