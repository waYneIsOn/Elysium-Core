/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICESTARTMODE
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICESTARTMODE

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ServiceStartMode : uint32_t
#elif defined(__ANDROID__)
	enum class ServiceStartMode
#else
#error "undefined os"
#endif
	{
		Boot = 0,
		System = 1,
		Automatic = 2,
		Manual = 3,
		Disabled = 4,
	};

	inline ServiceStartMode operator|(ServiceStartMode lhs, ServiceStartMode rhs)
	{
		return static_cast<ServiceStartMode>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}
	inline ServiceStartMode operator&(ServiceStartMode lhs, ServiceStartMode rhs)
	{
		return static_cast<ServiceStartMode>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}
}
#endif
