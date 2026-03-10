/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CRITICALSECTION
#define ELYSIUM_CORE_TEMPLATE_THREADING_CRITICALSECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
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
	/// 
	/// </summary>
	class CriticalSection final
	{
	public:
		CriticalSection();

		CriticalSection(const CriticalSection& Source) = delete;

		CriticalSection(CriticalSection&& Right) noexcept = delete;

		~CriticalSection();
	public:
		CriticalSection& operator=(const CriticalSection& Source) = delete;

		CriticalSection& operator=(CriticalSection&& Right) noexcept = delete;
	public:
		const bool Enter(const bool Blocking = true) noexcept;

		void Exit() noexcept;
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		CRITICAL_SECTION _Handle;
#elif defined ELYSIUM_CORE_OS_LINUX
		pthread_mutex_t _Handle;	// There is no pendant for CRITICAL_SECTION so I use a mutex instead
#else
#error "unsupported os"
#endif
	};
	
	inline Elysium::Core::Template::Threading::CriticalSection::CriticalSection()
		: _Handle()
	{
		InitializeCriticalSection(&_Handle);
	}

	inline Elysium::Core::Template::Threading::CriticalSection::~CriticalSection()
	{
		DeleteCriticalSection(&_Handle);
	}

	inline const bool Elysium::Core::Template::Threading::CriticalSection::Enter(const bool Blocking) noexcept
	{
		if (TryEnterCriticalSection(&_Handle) == 0)
		{
			if (!Blocking)
			{
				return false;
			}
			EnterCriticalSection(&_Handle);
		}
		return true;
	}

	inline void Elysium::Core::Template::Threading::CriticalSection::Exit() noexcept
	{
		LeaveCriticalSection(&_Handle);
	}
}
#endif
