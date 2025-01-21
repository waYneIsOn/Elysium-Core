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

		Thread& operator=(Thread&& Right) noexcept = delete;
	public:
		//static const Elysium::Core::uint32_t GetCurrentThreadId();
	public:
		//const Elysium::Core::uint32_t GetThreadId() const;
	public:
		//static void Sleep(const TimeSpan& Timeout);
	private:
		//static void ThreadMain();
	private:
		void* _Instance;
		void  (*_FunctionOrStaticMethod)();

#ifdef ELYSIUM_CORE_OS_WINDOWS
		HANDLE _ThreadHandlke;
#endif
	};

	inline constexpr Thread::Thread() noexcept
		: _Instance(nullptr), _FunctionOrStaticMethod(nullptr)
#ifdef ELYSIUM_CORE_OS_WINDOWS
		, _ThreadHandlke(INVALID_HANDLE_VALUE)
#endif
	{ }

	inline constexpr Thread::Thread(const Elysium::Core::Template::Container::Function<void(*)()>&ThreadStart) noexcept
		: _Instance(nullptr), _FunctionOrStaticMethod(ThreadStart._FunctionOrStaticMethod)
#ifdef ELYSIUM_CORE_OS_WINDOWS
		, _ThreadHandlke(INVALID_HANDLE_VALUE)
#endif
	{ }

	inline constexpr Thread::~Thread() noexcept
	{
#ifdef ELYSIUM_CORE_OS_WINDOWS
		if (_ThreadHandlke != INVALID_HANDLE_VALUE)
		{

		}
#endif

		_FunctionOrStaticMethod = nullptr;
		_Instance = nullptr;
	}
}
#endif
