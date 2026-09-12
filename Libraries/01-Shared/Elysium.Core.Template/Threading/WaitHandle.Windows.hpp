/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// Encapsulates operating system-specific objects that wait for exclusive access to shared resources.
	/// </summary>
	class WaitHandle
	{
	public:
		constexpr WaitHandle() = delete;
	protected:
		inline constexpr WaitHandle(HANDLE Handle)
			: _Handle(Handle)
		{ }
	public:
		constexpr WaitHandle(const WaitHandle& Source) = delete;

		constexpr WaitHandle(WaitHandle&& Right) noexcept = delete;

		inline constexpr virtual ~WaitHandle()
		{
			Close();
		}
	public:
		constexpr WaitHandle& operator=(const WaitHandle& Source) = delete;

		constexpr WaitHandle& operator=(WaitHandle&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Releases all resources held by the current WaitHandle.
		/// </summary>
		inline virtual constexpr void Close()
		{
			if (_Handle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(_Handle);
				_Handle = INVALID_HANDLE_VALUE;
			}
		}

		/// <summary>
		/// Blocks the current thread until the current instance receives a signal, using a 32-bit unsigned integer to specify the time interval and 
		/// specifying whether to exit the synchronization domain before the wait.
		/// </summary>
		inline virtual const bool WaitOne(const Elysium::Core::Template::System::uint32_t MillisecondsTimeout = 0xFFFFFFFF, const bool ExitContext = false) const
		{
			// @ToDo: ExitContext

			return WaitForSingleObject(_Handle, MillisecondsTimeout) == WAIT_OBJECT_0;
		}
	public:
		//static const bool SignalAndWait(WaitHandle& ToSignal, WaitHandle& ToWaitOn);

		//static const System::size WaitAll(WaitHandle[] WaitHandles, const System::uint32_t MillisecondsTimeout, const bool ExitContext);

		//static const System::size WaitAny(WaitHandle[] WaitHandles, const System::uint32_t MillisecondsTimeout, const bool ExitContext);
	public:
		static constexpr const Elysium::Core::Template::System::uint32_t WaitTimeout = 258;
	protected:
		HANDLE _Handle;
	};
}
#endif
#endif
