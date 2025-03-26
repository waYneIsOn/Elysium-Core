/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICESTARTMODE
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICESTARTMODE

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
	enum class ServiceStartMode : Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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

	inline ServiceStartMode operator|(ServiceStartMode Left, ServiceStartMode Right)
	{
		return static_cast<ServiceStartMode>(static_cast<int>(Left) | static_cast<int>(Right));
	}
	inline ServiceStartMode operator&(ServiceStartMode Left, ServiceStartMode Right)
	{
		return static_cast<ServiceStartMode>(static_cast<int>(Left) & static_cast<int>(Right));
	}
}
#endif
