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
	using ByteString = Collections::Template::StringBase<byte>;
	using CharString = Collections::Template::StringBase<char>;
	using WideString = Collections::Template::StringBase<wchar_t>;
	using String = Collections::Template::StringBase<char16_t>;
	using Ut32String = Collections::Template::StringBase<char32_t>;
}
#endif
