/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_STRING
#define ELYSIUM_CORE_STRING

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGBASE
#include "StringBase.hpp"
#endif

#pragma warning( disable : 4251 )

namespace Elysium::Core
{
	using ByteString = Collections::Template::StringBase<unsigned char>;
	using CharString = Collections::Template::StringBase<char>;
	using WideString = Collections::Template::StringBase<wchar_t>;
	using String = Collections::Template::StringBase<char16_t>;
	using Ut32String = Collections::Template::StringBase<char32_t>;
}
#endif
