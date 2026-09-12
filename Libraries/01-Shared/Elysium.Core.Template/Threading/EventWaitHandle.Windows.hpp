/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#ifndef _WINDOWS_
#define _WINSOCKAPI_ // don't include winsock
#include <Windows.h>
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// Represents a thread synchronization event.
	/// </summary>
	class EventWaitHandle
		: public WaitHandle
	{
	public:
		constexpr EventWaitHandle() = delete;
	protected:
		inline constexpr EventWaitHandle(const bool ManualReset, const bool InitialState, const char8_t* Name)
			: WaitHandle(CreateEventW(nullptr, ManualReset, InitialState, nullptr))
		{ }
	public:
		constexpr EventWaitHandle(const EventWaitHandle& Source) = delete;

		constexpr EventWaitHandle(EventWaitHandle&& Right) noexcept = delete;

		constexpr virtual ~EventWaitHandle() = default;
	public:
		constexpr EventWaitHandle& operator=(const EventWaitHandle& Source) = delete;

		constexpr EventWaitHandle& operator=(EventWaitHandle&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Sets the state of the event to signaled, allowing one or more waiting threads to proceed.
		/// </summary>
		/// <returns></returns>
		inline const bool Set()
		{
			BOOL Result = SetEvent(_Handle);
			return TRUE == Result;
		}

		/// <summary>
		/// Sets the state of the event to nonsignaled, causing threads to block.
		/// </summary>
		/// <returns></returns>
		inline const bool Reset()
		{
			BOOL Result = ResetEvent(_Handle);
			return TRUE == Result;
		}
	};
}
#endif
#endif
