/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS
#define ELYSIUM_CORE_SERVICEPROCESS_POWERBROADCASTSTATUS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class PowerBroadcastStatus : uint32_t
#elif defined(__ANDROID__)
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
