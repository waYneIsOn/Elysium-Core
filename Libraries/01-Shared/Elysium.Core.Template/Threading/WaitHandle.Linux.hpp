/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE_LINUX
#define ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE_LINUX

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_LINUX || defined ELYSIUM_CORE_OS_ANDROID

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// Encapsulates operating system-specific objects that wait for exclusive access to shared resources.
	/// </summary>
	class WaitHandle
	{
	public:
		constexpr WaitHandle() = delete;
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
			throw 1;
		}

		/// <summary>
		/// Blocks the current thread until the current instance receives a signal, using a 32-bit unsigned integer to specify the time interval and 
		/// specifying whether to exit the synchronization domain before the wait.
		/// </summary>
		inline virtual const bool WaitOne(const Elysium::Core::Template::System::uint32_t MillisecondsTimeout = 0xFFFFFFFF, const bool ExitContext = false) const
		{
			throw 1;
		}
	public:
		//static const bool SignalAndWait(WaitHandle& ToSignal, WaitHandle& ToWaitOn);

		//static const System::size WaitAll(WaitHandle[] WaitHandles, const System::uint32_t MillisecondsTimeout, const bool ExitContext);

		//static const System::size WaitAny(WaitHandle[] WaitHandles, const System::uint32_t MillisecondsTimeout, const bool ExitContext);
	public:
		inline static constexpr const Elysium::Core::Template::System::uint32_t WaitTimeout = 258;
	};
}
#endif
#endif
