/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON
#define ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON

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
	enum class SessionChangeReason : Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class SessionChangeReason
#else
#error "undefined os"
#endif
	{
		ConsoleConnect = 1,

		ConsoleDisconnect = 2,

		RemoteConnect = 3,

		RemoteDisconnect = 4,

		SessionLogon = 5,

		SessionLogoff = 6,

		SessionLock = 7,

		SessionUnlock = 8,

		SessionRemoteControl = 9
	};
}
#endif
