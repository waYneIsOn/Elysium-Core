/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERPERMISSIONACCESS
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERPERMISSIONACCESS

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ServiceControllerPermissionAccess : uint32_t
#elif defined(__ANDROID__)
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
