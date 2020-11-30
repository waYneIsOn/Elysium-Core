/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_THREADSTATE
#define ELYSIUM_CORE_THREADING_THREADSTATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
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