/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE
#define ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
#elif defined ELYSIUM_CORE_OS_LINUX

#elif defined ELYSIUM_CORE_OS_ANDROID

#else
	#error "unsupported os"
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// Encapsulates operating system-specific objects that wait for exclusive access to shared resources.
	/// </summary>
	class WaitHandle
	{
	protected:
		WaitHandle(HANDLE Handle);
	public:
		WaitHandle() = delete;

		WaitHandle(const WaitHandle& Source) = delete;

		WaitHandle(WaitHandle&& Right) noexcept = delete;

		~WaitHandle();
	public:
		WaitHandle& operator=(const WaitHandle& Source) = delete;

		WaitHandle& operator=(WaitHandle&& Right) noexcept = delete;
	public:
		/// <summary>
		/// Releases all resources held by the current WaitHandle.
		/// </summary>
		virtual void Close();

		/// <summary>
		/// Blocks the current thread until the current instance receives a signal, using a 32-bit unsigned integer to specify the time interval and 
		/// specifying whether to exit the synchronization domain before the wait.
		/// </summary>
		virtual const bool WaitOne(const System::uint32_t MillisecondsTimeout = 0xFFFFFFFF, const bool ExitContext = false) const;
	public:
		//static const bool SignalAndWait(WaitHandle& ToSignal, WaitHandle& ToWaitOn);

		//static const System::size WaitAll(WaitHandle[] WaitHandles, const System::uint32_t MillisecondsTimeout, const bool ExitContext);

		//static const System::size WaitAny(WaitHandle[] WaitHandles, const System::uint32_t MillisecondsTimeout, const bool ExitContext);
	public:
		static constexpr const System::uint32_t WaitTimeout = 258;
	protected:
		HANDLE _Handle;
	};

	inline Elysium::Core::Template::Threading::WaitHandle::WaitHandle(HANDLE Handle)
		: _Handle(Handle)
	{ }

	inline Elysium::Core::Template::Threading::WaitHandle::~WaitHandle()
	{
		Close();
	}

	inline void WaitHandle::Close()
	{
		if (_Handle != nullptr)
		{
#if defined ELYSIUM_CORE_OS_WINDOWS
			CloseHandle(_Handle);
#elif defined ELYSIUM_CORE_OS_LINUX

#else
#error "unsupported os"
#endif
			_Handle = nullptr;
		}
	}

	inline const bool WaitHandle::WaitOne(const System::uint32_t MillisecondsTimeout, const bool ExitContext) const
	{
		return WaitForSingleObject(_Handle, MillisecondsTimeout) == WAIT_OBJECT_0;
	}
}
#endif
