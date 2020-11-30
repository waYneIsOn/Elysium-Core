/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_EVENTWAITHANDLE
#define ELYSIUM_CORE_THREADING_EVENTWAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Threading
{
	// Represents a thread synchronization event.
	class ELYSIUM_CORE_API EventWaitHandle : public WaitHandle
	{
	public:
		EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const String& Name);
		EventWaitHandle(const EventWaitHandle& Source) = delete;
		EventWaitHandle(EventWaitHandle&& Right) noexcept = delete;
		virtual ~EventWaitHandle();

		EventWaitHandle& operator=(const EventWaitHandle& Source) = delete;
		EventWaitHandle& operator=(EventWaitHandle&& Right) noexcept = delete;

		// Sets the state of the event to signaled, allowing one or more waiting threads to proceed.
		const bool Set() const;

		// Sets the state of the event to nonsignaled, causing threads to block.
		const bool Reset() const;
	};
}
#endif
