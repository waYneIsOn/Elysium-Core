/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERSTATUS
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERSTATUS

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
	enum class ServiceControllerStatus : Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class ServiceControllerStatus
#else
#error "undefined os"
#endif
	{
		Stopped = 1,

		StartPending = 2,

		StopPending = 3,

		Running = 4,

		ContinuePending = 5,

		PausePending = 6,

		Paused = 7
	};
}
#endif
