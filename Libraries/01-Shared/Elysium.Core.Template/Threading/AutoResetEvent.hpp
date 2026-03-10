/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT
#define ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#include "EventWaitHandle.hpp"
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
	/// Represents a thread synchronization event that, when signaled, resets automatically after releasing a single waiting thread.
	/// This class cannot be inherited.
	/// </summary>
	class AutoResetEvent final 
		: public EventWaitHandle
	{
	public:
		AutoResetEvent(const bool InitialState);

		AutoResetEvent(const AutoResetEvent& Source) = delete;

		AutoResetEvent(AutoResetEvent&& Right) noexcept = delete;

		virtual ~AutoResetEvent();
	public:
		AutoResetEvent& operator=(const AutoResetEvent& Source) = delete;

		AutoResetEvent& operator=(AutoResetEvent&& Right) noexcept = delete;
	};

	inline Elysium::Core::Template::Threading::AutoResetEvent::AutoResetEvent(const bool InitialState)
		: EventWaitHandle(true, InitialState, nullptr)
	{ }

	inline Elysium::Core::Template::Threading::AutoResetEvent::~AutoResetEvent()
	{ }
}
#endif
