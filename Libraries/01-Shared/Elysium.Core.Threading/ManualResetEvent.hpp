/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#define ELYSIUM_CORE_THREADING_MANUALRESETEVENT

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
	public:
		ManualResetEvent& operator=(const ManualResetEvent& Source) = delete;

		ManualResetEvent& operator=(ManualResetEvent&& Right) noexcept = delete;
	};
}
#endif
