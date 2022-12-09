/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATEPART
#define ELYSIUM_CORE_DATEPART

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
	enum class DatePart : Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class DatePart
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		Year = 0,

		/// <summary>
		/// 
		/// </summary>
		DayOfYear = 1,

		/// <summary>
		/// 
		/// </summary>
		Month = 2,

		/// <summary>
		/// 
		/// </summary>
		Day = 3
	};
}
#endif
