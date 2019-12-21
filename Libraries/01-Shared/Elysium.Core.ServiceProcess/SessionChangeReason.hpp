/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON
#define ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SessionChangeReason : uint32_t
#elif defined(__ANDROID__)
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
