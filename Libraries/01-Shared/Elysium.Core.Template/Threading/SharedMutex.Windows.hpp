/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SHAREDMUTEX_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_SHAREDMUTEX_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
	
#ifndef _SYNCHAPI_H_
#include <synchapi.h>
#endif

#ifndef CONCURRENCYSAL_H
#include <concurrencysal.h>
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// 
	/// 
	/// https://learn.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--locks
	/// </summary>
	class SharedMutex
	{
	public:
		inline constexpr SharedMutex() noexcept
			: _Handle(SRWLOCK_INIT)
		{	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initializesrwlock
			//InitializeSRWLock(&_Handle);

			//assert(_Handle.Ptr == nullptr);
		}

		constexpr SharedMutex(const SharedMutex& Source) = delete;

		constexpr SharedMutex(SharedMutex&& Right) noexcept = delete;

		constexpr ~SharedMutex() noexcept = default;
	public:
		constexpr SharedMutex& operator=(const SharedMutex& Source) = delete;

		constexpr SharedMutex& operator=(SharedMutex&& Right) noexcept = delete;
	public:
		inline bool TryLockExlusive() noexcept
		{
			// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-tryacquiresrwlockexclusive
			return TryAcquireSRWLockExclusive(&_Handle) != 0;
		}

		inline void LockExclusive() noexcept
		{
			// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-acquiresrwlockexclusive
			//_Analysis_assume_lock_released_(_Handle);



			AcquireSRWLockExclusive(&_Handle);
		}

		inline void UnlockExclusive() noexcept
		{
			// https://learn.microsoft.com/en-us/cpp/code-quality/c26110?view=msvc-170
			// https://learn.microsoft.com/en-us/cpp/code-quality/annotating-locking-behavior?view=msvc-170
			// https://learn.microsoft.com/en-us/cpp/code-quality/how-to-specify-additional-code-information-by-using-analysis-assume?view=msvc-170
			_Analysis_assume_lock_held_(_Handle);

			// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasesrwlockexclusive
			ReleaseSRWLockExclusive(&_Handle);
		}
	public:
		inline bool TryLockShared() noexcept
		{
			// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-tryacquiresrwlockshared
			return TryAcquireSRWLockShared(&_Handle) != 0;
		}

		inline void LockShared() noexcept
		{
			// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-acquiresrwlockshared
			AcquireSRWLockShared(&_Handle);
		}

		inline void UnlockShared() noexcept
		{
			// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasesrwlockshared
			ReleaseSRWLockShared(&_Handle);
		}
	private:
		SRWLOCK _Handle;
	};
}
#endif
#endif
