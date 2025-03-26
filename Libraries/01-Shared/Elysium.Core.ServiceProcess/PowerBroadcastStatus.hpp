/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS
#define ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS

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
	enum class PowerBroadcastStatus : Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class PowerBroadcastStatus
#else
#error "undefined os"
#endif
	{
		QuerySuspend = 0,

		QuerySuspendFailed = 2,

		Suspend = 4,

		ResumeCritical = 6,

		ResumeSuspend = 7,

		BatteryLow = 9,

		PowerStatusChange = 10,

		OemEvent = 11,

		ResumeAutomatic = 18
	};
}
#endif
