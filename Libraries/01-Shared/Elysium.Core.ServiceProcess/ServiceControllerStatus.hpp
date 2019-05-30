/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERSTATUS
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERSTATUS

namespace Elysium
{
	namespace Core
	{
		namespace ServiceProcess
		{
			enum class ServiceControllerStatus : int
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
	}
}
#endif
