/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICEACCOUNT
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICEACCOUNT

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ServiceAccount : uint32_t
#elif defined(__ANDROID__)
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
