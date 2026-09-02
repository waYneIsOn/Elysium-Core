/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASKSTATUS
#define ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASKSTATUS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Threading::Tasks
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class TaskStatus
		: Elysium::Core::Template::System::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TaskStatus
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// The task has been initialized but has not yet been scheduled.
		/// </summary>
		Created = 0,

		/// <summary>
		/// The task is waiting to be activated and scheduled internally.
		/// </summary>
		WaitingForActivation = 1,

		/// <summary>
		/// The task has been scheduled for execution but has not yet begun executing.
		/// </summary>
		WaitingToRun = 2,

		/// <summary>
		/// The task is running but has not yet completed.
		/// </summary>
		Running = 3,

		/// <summary>
		/// The task has finished executing and is implicitly waiting for attached child tasks to complete.
		/// </summary>
		WaitingForChildrenToComplete = 4,

		/// <summary>
		/// The task completed execution successfully.
		/// </summary>
		RanToCompletion = 5,

		/// <summary>
		/// ...
		/// </summary>
		Canceled = 6,

		/// <summary>
		/// The task completed due to an unhandled exception.
		/// </summary>
		Faulted = 7
	};
}
#endif
