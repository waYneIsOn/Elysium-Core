/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#include "EventWaitHandle.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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
		inline constexpr AutoResetEvent(const bool InitialState = false)
			: EventWaitHandle(false, InitialState, nullptr)
		{ }

		AutoResetEvent(const AutoResetEvent& Source) = delete;

		AutoResetEvent(AutoResetEvent&& Right) noexcept = delete;

		virtual ~AutoResetEvent() = default;
	public:
		AutoResetEvent& operator=(const AutoResetEvent& Source) = delete;

		AutoResetEvent& operator=(AutoResetEvent&& Right) noexcept = delete;
	};
}
#endif
#endif
