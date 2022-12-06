/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT
#define ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT

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
	/// Represents a thread synchronization event that, when signaled, must be reset manually.
	/// This class cannot be inherited.
	/// </summary>
	class ManualResetEvent final : public EventWaitHandle
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

	inline Elysium::Core::Template::Threading::ManualResetEvent::ManualResetEvent(const bool InitialState)
		: EventWaitHandle(false, InitialState, nullptr)
	{ }

	inline Elysium::Core::Template::Threading::ManualResetEvent::~ManualResetEvent()
	{ }
}
#endif
