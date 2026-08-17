/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIMEKIND
#define ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIMEKIND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Chrono
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class DateTimeKind
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class DateTimeKind
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		Unspecified = 0,

		/// <summary>
		/// 
		/// </summary>
		Utc = 1,

		/// <summary>
		/// 
		/// </summary>
		Local = 2
	};
}
#endif
