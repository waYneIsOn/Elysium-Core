/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_AUTORESETEVENT
#define ELYSIUM_CORE_THREADING_AUTORESETEVENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_THREADING_EVENTWAITHANDLE
#include "EventWaitHandle.hpp"
#endif

namespace Elysium::Core::Threading
{
	// Represents a thread synchronization event that, when signaled, resets automatically after releasing a single waiting thread. This class cannot be inherited.
	class ELYSIUM_CORE_API AutoResetEvent final : public EventWaitHandle
	{
	public:
		AutoResetEvent(const bool InitialState);
		AutoResetEvent(const AutoResetEvent& Source) = delete;
		AutoResetEvent(AutoResetEvent&& Right) noexcept = delete;
		virtual ~AutoResetEvent();

		AutoResetEvent& operator=(const AutoResetEvent& Source) = delete;
		AutoResetEvent& operator=(AutoResetEvent&& Right) noexcept = delete;
	};
}
#endif
