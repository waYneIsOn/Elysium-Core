/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_EVENTWAITHANDLE
#define ELYSIUM_CORE_THREADING_EVENTWAITHANDLE

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Threading
{
	// Represents a thread synchronization event.
	class ELYSIUM_CORE_API EventWaitHandle
	{
	public:
		EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const WideString& Name);
		EventWaitHandle(const EventWaitHandle& Source) = delete;
		EventWaitHandle(EventWaitHandle&& Right) noexcept = delete;
		~EventWaitHandle();

		EventWaitHandle& operator=(const EventWaitHandle& Source) = delete;
		EventWaitHandle& operator=(EventWaitHandle&& Right) noexcept = delete;

		const bool Set();
		const bool Reset();
		const bool Wait();
	private:
		ELYSIUM_SIGNAL_HANDLE _Handle;
	};
}
#endif
