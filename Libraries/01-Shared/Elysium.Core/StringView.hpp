/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_STRINGVIEW
#define ELYSIUM_CORE_STRINGVIEW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_STRINGVIEWBASE
#include "StringViewBase.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#pragma warning( disable : 4251 )

namespace Elysium::Core
{
	using StringView = Collections::Template::StringViewBase<char>;
	using WideStringView = Collections::Template::StringViewBase<wchar_t>;
}
#endif
