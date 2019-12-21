/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_STRINGVIEW
#define ELYSIUM_CORE_STRINGVIEW

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGVIEWBASE
#include "StringViewBase.hpp"
#endif

#pragma warning( disable : 4251 )

namespace Elysium::Core
{
	using ByteStringView = Collections::Template::StringViewBase<unsigned char>;
	using CharStringView = Collections::Template::StringViewBase<char>;
	using WideStringView = Collections::Template::StringViewBase<wchar_t>;
	using StringView = Collections::Template::StringViewBase<char16_t>;
	using Ut32StringView = Collections::Template::StringViewBase<char32_t>;
}
#endif
