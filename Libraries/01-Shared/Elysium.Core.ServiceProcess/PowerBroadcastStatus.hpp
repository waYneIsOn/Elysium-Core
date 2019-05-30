/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS
#define ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS

namespace Elysium
{
	namespace Core
	{
		namespace ServiceProcess
		{
			enum class PowerBroadcastStatus : int
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
	}
}
#endif
