/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#define ELYSIUM_CORE_THREADING_AUTORESETEVENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_THREADING_EVENTWAITHANDLE
#include "EventWaitHandle.hpp"
#endif

namespace Elysium::Core::Threading
{
	// Represents a thread synchronization event that, when signaled, must be reset manually. This class cannot be inherited.
	class ELYSIUM_CORE_API ManualResetEvent final : public EventWaitHandle
	{
	public:
		ManualResetEvent(const bool InitialState);
		ManualResetEvent(const ManualResetEvent& Source) = delete;
		ManualResetEvent(ManualResetEvent&& Right) noexcept = delete;
		virtual ~ManualResetEvent();

		ManualResetEvent& operator=(const ManualResetEvent& Source) = delete;
		ManualResetEvent& operator=(ManualResetEvent&& Right) noexcept = delete;
	};
}
#endif
