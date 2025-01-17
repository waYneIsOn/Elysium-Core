/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREAD
#define ELYSIUM_CORE_TEMPLATE_THREADING_THREAD

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FUNCTION
#include "../Container/Function.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../OperatingSystem.hpp"
#endif

#ifdef ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
#else
#error "unsupported os"
#endif

namespace Elysium::Core::Template::Threading
{
	class Thread final
	{
	private:
		constexpr Thread() noexcept;
	public:
		constexpr Thread(const Elysium::Core::Template::Container::Function<void(*)()>& ThreadStart) noexcept;

		constexpr Thread(const Thread& Source) = delete;

		constexpr Thread(Thread&& Right) noexcept = delete;

		constexpr ~Thread() noexcept;
	public:
		Thread& operator=(const Thread& Source) = delete;

		Thread& operator=(Thread&& Right) noexcept;
	public:
		//static const Elysium::Core::uint32_t GetCurrentThreadId();
	public:
		//const Elysium::Core::uint32_t GetThreadId() const;
	public:
		//static void Sleep(const TimeSpan& Timeout);
	private:
		//static void ThreadMain();
	private:
		void  (*_FunctionOrStaticMethod)();
	};

	inline constexpr Thread::Thread() noexcept
		: _FunctionOrStaticMethod(nullptr)
	{ }

	inline constexpr Thread::Thread(const Elysium::Core::Template::Container::Function<void(*)()>&ThreadStart) noexcept
		: _FunctionOrStaticMethod(ThreadStart._FunctionOrStaticMethod)
	{ }

	inline constexpr Thread::~Thread() noexcept
	{ }
}
#endif
