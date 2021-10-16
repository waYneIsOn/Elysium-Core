/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#define ELYSIUM_CORE_THREADING_WAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Threading
{
	// Encapsulates operating system-specific objects that wait for exclusive access to shared resources.
	class ELYSIUM_CORE_API WaitHandle
	{
	public:
		WaitHandle(const WaitHandle& Source) = delete;
		WaitHandle(WaitHandle&& Right) noexcept = delete;
		virtual ~WaitHandle();

		WaitHandle& operator=(const WaitHandle& Source) = delete;
		WaitHandle& operator=(WaitHandle&& Right) noexcept = delete;

		// Blocks the current thread until the current WaitHandle receives a signal.
		virtual const bool WaitOne() const;

		// Blocks the current thread until the current instance receives a signal, using a TimeSpan to specify the time interval.
		virtual const bool WaitOne(const Elysium::Core::TimeSpan& Timeout) const;

		// Blocks the current thread until the current instance receives a signal, using a 32-bit signed integer to specify the time interval in milliseconds.
		virtual const bool WaitOne(const Elysium::Core::int32_t MillisecondsTimeout) const;

		// Blocks the current thread until the current instance receives a signal, using a TimeSpan to specify the time interval and specifying whether to exit the synchronization domain before the wait.
		virtual const bool WaitOne(const Elysium::Core::TimeSpan& Timeout, const bool ExitContext) const;

		// Blocks the current thread until the current instance receives a signal, using a 32-bit signed integer to specify the time interval and specifying whether to exit the synchronization domain before the wait.
		virtual const bool WaitOne(const Elysium::Core::int32_t MillisecondsTimeout, const bool ExitContext) const;
	protected:
		WaitHandle(const ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE Handle);

		const ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE _Handle;
	};
}
#endif
