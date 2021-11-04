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

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Threading::Tasks
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TaskStatus : Elysium::Core::uint32_t
#elif defined(__ANDROID__)
	enum class TaskStatus
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		Created = 0,

		/// <summary>
		/// 
		/// </summary>
		WaitingForActivation = 1,

		/// <summary>
		/// 
		/// </summary>
		WaitingToRun = 2,

		/// <summary>
		/// 
		/// </summary>
		Running = 3,

		/// <summary>
		/// 
		/// </summary>
		WaitingForChildrenToComplete = 4,

		/// <summary>
		/// 
		/// </summary>
		RanToCompletion = 5,

		/// <summary>
		/// 
		/// </summary>
		Canceled = 6,

		/// <summary>
		/// 
		/// </summary>
		Faulted = 7
	};
}
#endif