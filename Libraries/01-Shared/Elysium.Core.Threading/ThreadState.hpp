/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_THREADSTATE
#define ELYSIUM_CORE_THREADING_THREADSTATE

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Threading
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ThreadState : uint32_t
#elif defined(__ANDROID__)
	enum class ThreadState
#else
#error "undefined os"
#endif
	{
		Running = 0,
		StopRequested = 1,
		SuspendRequested = 2,
		Background = 4,
		Unstarted = 8,
		Stopped = 16,
		WaitSleepJoin = 32,
		Suspended = 64,
		AbortRequested = 128,
		Aborted = 256
	};

	inline ThreadState operator|(ThreadState lhs, ThreadState rhs)
	{
		return static_cast<ThreadState>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
	}
	inline ThreadState operator&(ThreadState lhs, ThreadState rhs)
	{
		return static_cast<ThreadState>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
	}
}
#endif