/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO
#define ELYSIUM_CORE_GLOBALIZATION_CULTUREINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTUREINFO
#include "../Elysium.Core.Template/CultureInfo.hpp"
#endif

namespace Elysium::Core::Globalization
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::CultureInfo<char>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::CultureInfo<char8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::CultureInfo<char16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::CultureInfo<char32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::CultureInfo<wchar_t>;
	
	using CultureInfo = Elysium::Core::Template::Globalization::CultureInfo<char>;
	using Utf8CultureInfo = Elysium::Core::Template::Globalization::CultureInfo<char8_t>;
	using Utf16CultureInfo = Elysium::Core::Template::Globalization::CultureInfo<char16_t>;
	using Utf32CultureInfo = Elysium::Core::Template::Globalization::CultureInfo<char32_t>;
	using WideCultureInfo = Elysium::Core::Template::Globalization::CultureInfo<wchar_t>;
}
#endif
