/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_TASKS_TASKSTATUS
#define ELYSIUM_CORE_THREADING_TASKS_TASKSTATUS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
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