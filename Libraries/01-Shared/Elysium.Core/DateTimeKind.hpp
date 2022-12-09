/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATETIMEKIND
#define ELYSIUM_CORE_DATETIMEKIND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class DateTimeKind : Template::System::uint8_t
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