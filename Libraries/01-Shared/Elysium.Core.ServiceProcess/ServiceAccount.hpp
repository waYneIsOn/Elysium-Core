/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICEACCOUNT
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICEACCOUNT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ServiceAccount : Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ServiceAccount
#else
#error "undefined os"
#endif
	{
		LocalService = 0,

		NetworkService = 1,

		LocalSystem = 2,

		User = 3,
	};
}
#endif
