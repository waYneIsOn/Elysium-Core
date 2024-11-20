/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#define ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
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
	/// A synchronization primitive that can also be used for interprocess synchronization.
	/// </summary>
	class Mutex final 
		: public WaitHandle
	{
	public:
		Mutex(const bool InitiallyOwned = false, const char8_t* Name = nullptr);

		Mutex(const Mutex& Source) = delete;

		Mutex(Mutex&& Right) noexcept = delete;

		~Mutex();
	public:
		Mutex& operator=(const Mutex& Source) = delete;

		Mutex& operator=(Mutex&& Right) noexcept = delete;
	public:
		void Release();
	};

	inline Elysium::Core::Template::Threading::Mutex::Mutex(const bool InitiallyOwned, const char8_t* Name)
		: WaitHandle(CreateMutexW(nullptr, false, nullptr))
	{ }

	inline Elysium::Core::Template::Threading::Mutex::~Mutex()
	{ }

	inline void Elysium::Core::Template::Threading::Mutex::Release()
	{
		BOOL WasReleased = ReleaseMutex(_Handle);
	}
}
#endif
