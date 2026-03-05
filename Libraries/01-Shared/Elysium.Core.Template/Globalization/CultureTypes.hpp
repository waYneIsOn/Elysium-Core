/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTURETYPES
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_CULTURETYPES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::Globalization
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class CultureTypes : System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class CultureTypes
#else
#error "undefined os"
#endif
	{
		NeutralCultures = 1,

		SpecificCultures = 2,

		InstalledCultures = 4,

		AllCultures = 7,
	};

	inline CultureTypes operator|(CultureTypes Left, CultureTypes Right)
	{
		return static_cast<CultureTypes>(static_cast<System::uint8_t>(Left) | static_cast<System::uint8_t>(Right));
	}
	inline CultureTypes operator&(CultureTypes Left, CultureTypes Right)
	{
		return static_cast<CultureTypes>(static_cast<System::uint8_t>(Left) & static_cast<System::uint8_t>(Right));
	}
}
#endif
