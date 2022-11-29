/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_REGIONINFO
#define ELYSIUM_CORE_GLOBALIZATION_REGIONINFO

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_REGIONINFO
#include "../Elysium.Core.Template/RegionInfo.hpp"
#endif

namespace Elysium::Core::Globalization
{
	/*
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::RegionInfo<char>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::RegionInfo<char8_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::RegionInfo<char16_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::RegionInfo<char32_t>;
	template class ELYSIUM_CORE_API Elysium::Core::Template::Globalization::RegionInfo<wchar_t>;
	*/
	using RegionInfo = Elysium::Core::Template::Globalization::RegionInfo<char>;
	using Utf8RegionInfo = Elysium::Core::Template::Globalization::RegionInfo<char8_t>;
	using Utf16RegionInfo = Elysium::Core::Template::Globalization::RegionInfo<char16_t>;
	using Utf32RegionInfo = Elysium::Core::Template::Globalization::RegionInfo<char32_t>;
	using WideRegionInfo = Elysium::Core::Template::Globalization::RegionInfo<wchar_t>;
}
#endif
