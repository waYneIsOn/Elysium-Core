/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#include "EventWaitHandle.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// Represents a thread synchronization event that, when signaled, must be reset manually.
	/// This class cannot be inherited.
	/// </summary>
	class ManualResetEvent final 
		: public EventWaitHandle
	{
	public:
		inline constexpr ManualResetEvent(const bool InitialState = false)
			: EventWaitHandle(true, InitialState, nullptr)
		{ }

		constexpr ManualResetEvent(const ManualResetEvent& Source) = delete;

		constexpr ManualResetEvent(ManualResetEvent&& Right) noexcept = delete;

		constexpr virtual ~ManualResetEvent() = default;
	public:
		constexpr ManualResetEvent& operator=(const ManualResetEvent& Source) = delete;

		constexpr ManualResetEvent& operator=(ManualResetEvent&& Right) noexcept = delete;
	};
}
#endif
#endif
