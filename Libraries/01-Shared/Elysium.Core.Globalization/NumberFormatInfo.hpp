/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO
#define ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO
#include "../Elysium.Core.Template/NumberFormatInfo.hpp"
#endif

namespace Elysium::Core::Globalization
{
	/*
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::NumberFormatInfo<char>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::NumberFormatInfo<char8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::NumberFormatInfo<char16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::NumberFormatInfo<char32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>;
	*/
	using NumberFormatInfo = Elysium::Core::Template::Globalization::NumberFormatInfo<char>;
	using Utf8NumberFormatInfo = Elysium::Core::Template::Globalization::NumberFormatInfo<char8_t>;
	using Utf16NumberFormatInfo = Elysium::Core::Template::Globalization::NumberFormatInfo<char16_t>;
	using Utf32NumberFormatInfo = Elysium::Core::Template::Globalization::NumberFormatInfo<char32_t>;
	using WideNumberFormatInfo = Elysium::Core::Template::Globalization::NumberFormatInfo<wchar_t>;
}
#endif
