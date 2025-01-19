/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_LANGUAGETYPE
#define ELYSIUM_CORE_TEMPLATE_GLOBALIZATION_INTERNAL_LANGUAGETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

namespace Elysium::Core::Template::Globalization::Internal
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class LanguageType : System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class LanguageType
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Language is still currently in use/spoken.
		/// </summary>
		Living = 0,

		/// <summary>
		/// Language is no longer in use/spoken (like latin and ancient greek).
		/// </summary>
		Dead = 1,

		/// <summary>
		/// Language was artificially created (like klingon).
		/// </summary>
		Constructed = 2
	};
}
#endif
