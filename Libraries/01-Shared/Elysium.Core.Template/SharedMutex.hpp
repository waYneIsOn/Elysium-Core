/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SHAREDMUTEX
#define ELYSIUM_CORE_TEMPLATE_THREADING_SHAREDMUTEX

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _SYNCHAPI_H_
	#include <synchapi.h>
	#endif

	#ifndef CONCURRENCYSAL_H
	#include <concurrencysal.h>
	#endif
#else
#error "unsupported os"
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
		SharedMutex() noexcept;

		SharedMutex(const SharedMutex& Source) = delete;

		SharedMutex(SharedMutex&& Right) noexcept = delete;

		~SharedMutex() noexcept;
	public:
		SharedMutex& operator=(const SharedMutex& Source) = delete;

		SharedMutex& operator=(SharedMutex&& Right) noexcept = delete;
	public:
		bool TryLockExlusive() noexcept;

		void LockExclusive() noexcept;

		void UnlockExclusive() noexcept;
	public:
		bool TryLockShared() noexcept;

		void LockShared() noexcept;

		void UnlockShared() noexcept;
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		SRWLOCK _Handle;
#else
#error "unsupported os"
#endif
	};

	inline Elysium::Core::Template::Threading::SharedMutex::SharedMutex() noexcept
#if defined ELYSIUM_CORE_OS_WINDOWS
		: _Handle()
	{	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initializesrwlock
		InitializeSRWLock(&_Handle);
	}
#else
	{ }
#error "unsupported os"
#endif

	inline SharedMutex::~SharedMutex() noexcept
	{ }

	inline bool SharedMutex::TryLockExlusive() noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-tryacquiresrwlockexclusive
		return TryAcquireSRWLockExclusive(&_Handle) != 0;
#else
#error "unsupported os"
#endif
	}

	inline void SharedMutex::LockExclusive() noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-acquiresrwlockexclusive
		AcquireSRWLockExclusive(&_Handle);
#else
#error "unsupported os"
#endif
	}

	inline void SharedMutex::UnlockExclusive() noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		// https://learn.microsoft.com/en-us/cpp/code-quality/c26110?view=msvc-170
		// https://learn.microsoft.com/en-us/cpp/code-quality/annotating-locking-behavior?view=msvc-170
		// https://learn.microsoft.com/en-us/cpp/code-quality/how-to-specify-additional-code-information-by-using-analysis-assume?view=msvc-170
		_Analysis_assume_lock_held_(_Handle);

		// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasesrwlockexclusive
		ReleaseSRWLockExclusive(&_Handle);
#else
#error "unsupported os"
#endif
	}

	inline bool SharedMutex::TryLockShared() noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-tryacquiresrwlockshared
		return TryAcquireSRWLockShared(&_Handle) != 0;
#else
#error "unsupported os"
#endif
	}

	inline void SharedMutex::LockShared() noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-acquiresrwlockshared
		AcquireSRWLockShared(&_Handle);
#else
#error "unsupported os"
#endif
	}

	inline void SharedMutex::UnlockShared() noexcept
	{
#if defined ELYSIUM_CORE_OS_WINDOWS
		// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasesrwlockshared
		ReleaseSRWLockShared(&_Handle);
#else
#error "unsupported os"
#endif
	}
}
#endif
