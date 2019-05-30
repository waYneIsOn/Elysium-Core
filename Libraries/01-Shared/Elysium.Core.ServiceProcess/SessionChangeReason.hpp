/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON
#define ELYSIUM_CORE_SERVICEPROCESS_SESSIONCHANGEREASON

namespace Elysium
{
	namespace Core
	{
		namespace ServiceProcess
		{
			enum class SessionChangeReason : int
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
	}
}
#endif
