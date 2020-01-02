/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASKSTATUS
#define ELYSIUM_CORE_THREADING_TASKS_TASKSTATUS

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Threading::Tasks
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TaskStatus : uint32_t
#elif defined(__ANDROID__)
	enum class TaskStatus
#else
#error "undefined os"
#endif
	{
		Created = 0,
		WaitingForActivation = 1,
		WaitingToRun = 2,
		Running = 3,
		WaitingForChildrenToComplete = 4,
		RanToCompletion = 5,
		Canceled = 6,
		Faulted = 7
	};
}
#endif