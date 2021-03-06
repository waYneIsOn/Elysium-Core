/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_TASKS_TASKCREATIONOPTIONS
#define ELYSIUM_CORE_THREADING_TASKS_TASKCREATIONOPTIONS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Threading::Tasks
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TaskCreationOptions : uint32_t
#elif defined(__ANDROID__)
	enum class TaskCreationOptions
#else
#error "undefined os"
#endif
	{
		None = 0,
		PreferFairness = 1,
		LongRunning = 2,
		AttachToParent = 4,
		DenyChildAttachj = 8,
		HideScheduler = 16,
		RunContinuationsAsynchronously = 64
	};

	inline TaskCreationOptions operator|(TaskCreationOptions lhs, TaskCreationOptions rhs)
	{
		return static_cast<TaskCreationOptions>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
	}
	inline TaskCreationOptions operator&(TaskCreationOptions lhs, TaskCreationOptions rhs)
	{
		return static_cast<TaskCreationOptions>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
	}
}
#endif