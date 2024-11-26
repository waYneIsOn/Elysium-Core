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
	#ifndef _PTHREAD_H
	#include <pthread.h>
	#endif
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
#if defined ELYSIUM_CORE_OS_WINDOWS
		WaitHandle(HANDLE Handle);
#elif defined ELYSIUM_CORE_OS_LINUX
		WaitHandle(pthread_mutex_t Handle);
#else
#error "unsupported os"
#endif
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
#if defined ELYSIUM_CORE_OS_WINDOWS
		HANDLE _Handle;
#elif defined ELYSIUM_CORE_OS_LINUX
		pthread_mutex_t _Handle;
#else
#error "unsupported os"
#endif
	};

#if defined ELYSIUM_CORE_OS_WINDOWS
	inline Elysium::Core::Template::Threading::WaitHandle::WaitHandle(HANDLE Handle)
		: _Handle(Handle)
	{ }
#elif defined ELYSIUM_CORE_OS_LINUX
	inline WaitHandle::WaitHandle(pthread_mutex_t Handle)
		: _Handle(Handle)
	{
		//pthread_mutexattr_t MutexAttributes = pthread_mutexattr_t();
		pthread_mutex_init(&_Handle, nullptr);
	}
#else
#error "unsupported os"
#endif

	inline Elysium::Core::Template::Threading::WaitHandle::~WaitHandle()
	{
		Close();
	}

	inline void WaitHandle::Close()
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		if (_Handle != nullptr)
		{
			CloseHandle(_Handle);
			_Handle = nullptr;
		}
#elif defined ELYSIUM_CORE_OS_LINUX
		pthread_mutex_destroy(&_Handle);
#else
#error "unsupported os"
#endif
	}

	inline const bool WaitHandle::WaitOne(const System::uint32_t MillisecondsTimeout, const bool ExitContext) const
	{
		// @ToDo: ExitContext

#if defined ELYSIUM_CORE_OS_WINDOWS
		return WaitForSingleObject(_Handle, MillisecondsTimeout) == WAIT_OBJECT_0;
#elif defined ELYSIUM_CORE_OS_LINUX
		// @ToDo: set timespec/timeout values correctly
		timespec Timeout;
		Timeout.tv_nsec = 0;
		Timeout.tv_sec = 0;

		return pthread_mutex_timedlock(&_Handle, &Timeout) != 0;
#else
#error "unsupported os"
#endif
	}
}
#endif
