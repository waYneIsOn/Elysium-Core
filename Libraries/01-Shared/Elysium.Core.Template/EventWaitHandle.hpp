/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#define ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// Represents a thread synchronization event.
	/// </summary>
	class EventWaitHandle : public WaitHandle
	{
	public:
		EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const char8_t* Name);

		EventWaitHandle(const EventWaitHandle& Source) = delete;

		EventWaitHandle(EventWaitHandle&& Right) noexcept = delete;

		virtual ~EventWaitHandle();
	public:
		EventWaitHandle& operator=(const EventWaitHandle& Source) = delete;

		EventWaitHandle& operator=(EventWaitHandle&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Sets the state of the event to signaled, allowing one or more waiting threads to proceed.
		/// </summary>
		/// <returns></returns>
		const bool Set();

		/// <summary>
		/// Sets the state of the event to nonsignaled, causing threads to block.
		/// </summary>
		/// <returns></returns>
		const bool Reset();
	};
	
	inline Elysium::Core::Template::Threading::EventWaitHandle::EventWaitHandle(const bool AutomaticallyReset, const bool InitialState, const char8_t* Name)
		: WaitHandle(CreateEventW(nullptr, AutomaticallyReset, InitialState, nullptr))
	{ }

	inline Elysium::Core::Template::Threading::EventWaitHandle::~EventWaitHandle()
	{ }

	inline const bool Elysium::Core::Template::Threading::EventWaitHandle::Set()
	{
		return SetEvent(_Handle) == TRUE;
	}

	inline const bool Elysium::Core::Template::Threading::EventWaitHandle::Reset()
	{
		return ResetEvent(_Handle) == TRUE;
	}
}
#endif
