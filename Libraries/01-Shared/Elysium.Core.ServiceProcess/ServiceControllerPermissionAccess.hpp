/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERPERMISSIONACCESS
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERPERMISSIONACCESS

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
	enum class ServiceControllerPermissionAccess : Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ServiceControllerPermissionAccess
#else
#error "undefined os"
#endif
	{
		None = 0,

		Browse = 2,

		Control = 6,
	};
}
#endif
