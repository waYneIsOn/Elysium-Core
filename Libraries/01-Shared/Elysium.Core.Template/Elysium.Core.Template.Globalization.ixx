module;

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTUREINFO
#include "Globalization/CultureInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTURETYPES
#include "Globalization/CultureTypes.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_DIGITSHAPES
#include "Globalization/DigitShapes.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_NUMBERFORMATINFO
#include "Globalization/NumberFormatInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_REGIONINFO
#include "Globalization/RegionInfo.hpp"
#endif

export module Elysium.Core.Template.Globalization;

export
{
	using Elysium::Core::Template::Globalization::CultureInfo;
	using Elysium::Core::Template::Globalization::CultureTypes;
	using Elysium::Core::Template::Globalization::DigitShapes;
	using Elysium::Core::Template::Globalization::NumberFormatInfo;
	using Elysium::Core::Template::Globalization::RegionInfo;
}
