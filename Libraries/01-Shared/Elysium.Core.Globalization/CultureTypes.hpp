/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_GLOBALIZATION_CULTURETYPES
#define ELYSIUM_CORE_GLOBALIZATION_CULTURETYPES

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Globalization
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class CultureTypes : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
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
		return static_cast<CultureTypes>(static_cast<Elysium::Core::uint32_t>(Left) | static_cast<Elysium::Core::uint32_t>(Right));
	}
	inline CultureTypes operator&(CultureTypes Left, CultureTypes Right)
	{
		return static_cast<CultureTypes>(static_cast<Elysium::Core::uint32_t>(Left) & static_cast<Elysium::Core::uint32_t>(Right));
	}
}
#endif
