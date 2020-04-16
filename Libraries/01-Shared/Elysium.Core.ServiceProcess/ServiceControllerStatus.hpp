/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERSTATUS
#define ELYSIUM_CORE_SERVICEPROCESS_SERVICECONTROLLERSTATUS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::ServiceProcess
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ServiceControllerStatus : uint32_t
#elif defined(__ANDROID__)
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
