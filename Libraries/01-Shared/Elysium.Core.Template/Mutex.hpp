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
	/// A synchronization primitive that can also be used for interprocess synchronization.
	/// </summary>
	class Mutex final 
		: public WaitHandle
	{
	public:
		constexpr Mutex(const bool InitiallyOwned = false, const char8_t* Name = nullptr);

		constexpr Mutex(const Mutex& Source) = delete;

		constexpr Mutex(Mutex&& Right) noexcept = delete;

		constexpr virtual ~Mutex() override;
	public:
		constexpr Mutex& operator=(const Mutex& Source) = delete;

		constexpr Mutex& operator=(Mutex&& Right) noexcept = delete;
	public:
		void Lock();

		//bool TryLock();

		void Unlock();
	private:

	};

#if defined ELYSIUM_CORE_OS_WINDOWS
	inline constexpr Elysium::Core::Template::Threading::Mutex::Mutex(const bool InitiallyOwned, const char8_t* Name)
		: WaitHandle(CreateMutexW(nullptr, InitiallyOwned == true ? TRUE : FALSE, nullptr))
	{ }
#elif defined ELYSIUM_CORE_OS_LINUX
	inline Elysium::Core::Template::Threading::Mutex::Mutex(const bool InitiallyOwned, const char8_t* Name)
		: WaitHandle(PTHREAD_MUTEX_INITIALIZER)
	{ 
		if (InitiallyOwned)
		{	
			pthread_mutex_lock(&_Handle);
		}
	}
#else
#error "unsupported os"
#endif

	inline constexpr Elysium::Core::Template::Threading::Mutex::~Mutex()
	{
		// @ToDo: Parent destructor will call Close(). Do I need to release here beforehand though? need to write specific test!
	}

#if defined ELYSIUM_CORE_OS_WINDOWS
	inline void Elysium::Core::Template::Threading::Mutex::Lock()
	{
		DWORD WaitResult = WaitForSingleObject(_Handle, INFINITE);
		
		if (WAIT_OBJECT_0 == WaitResult)
		{
			bool bla = false;
		}
		else if (WAIT_ABANDONED == WaitResult)
		{
			bool blub = false;
		}
	}
	/*
	inline bool Elysium::Core::Template::Threading::Mutex::TryLock()
	{
		DWORD WaitResult = WaitForSingleObject(_Handle, INFINITE);

		if (WAIT_OBJECT_0 == WaitResult)
		{
			bool bla = false;
		}
		else if (WAIT_ABANDONED == WaitResult)
		{
			bool blub = false;
		}
	}
	*/
	inline void Elysium::Core::Template::Threading::Mutex::Unlock()
	{
		BOOL WasReleased = ReleaseMutex(_Handle);

		if (0 != WasReleased)
		{	// success
			bool bla = false;
		}
		else
		{
			DWORD LastError = GetLastError();
			bool blub = false;
		}
	}
#elif defined ELYSIUM_CORE_OS_LINUX
	inline void Elysium::Core::Template::Threading::Mutex::Release()
	{
		int WasReleased = pthread_mutex_unlock(&_Handle);
	}
#else
#error "unsupported os"
#endif
}
#endif
