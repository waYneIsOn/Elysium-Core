/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON
#define ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
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
