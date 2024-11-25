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

#ifndef _SYNCHAPI_H_
#include <synchapi.h>
#endif

namespace Elysium::Core::Template::Threading
{
	class SharedMutex
	{
	public:
		constexpr SharedMutex() noexcept;

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
		void* _Handle;
	};

	inline constexpr Elysium::Core::Template::Threading::SharedMutex::SharedMutex() noexcept
		: _Handle(nullptr)
	{ }

	inline SharedMutex::~SharedMutex() noexcept
	{ }

	inline bool SharedMutex::TryLockExlusive() noexcept
	{	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-tryacquiresrwlockexclusive
		return TryAcquireSRWLockExclusive(reinterpret_cast<PSRWLOCK>(&_Handle)) != 0;
	}

	inline void SharedMutex::LockExclusive() noexcept
	{	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-acquiresrwlockexclusive
		AcquireSRWLockExclusive(reinterpret_cast<PSRWLOCK>(&_Handle));
	}

	inline void SharedMutex::UnlockExclusive() noexcept
	{	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasesrwlockexclusive
		ReleaseSRWLockExclusive(reinterpret_cast<PSRWLOCK>(&_Handle));
	}

	inline bool SharedMutex::TryLockShared() noexcept
	{	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-tryacquiresrwlockshared
		return TryAcquireSRWLockShared(reinterpret_cast<PSRWLOCK>(&_Handle)) != 0;
	}

	inline void SharedMutex::LockShared() noexcept
	{	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-acquiresrwlockshared
		AcquireSRWLockShared(reinterpret_cast<PSRWLOCK>(&_Handle));
	}

	inline void SharedMutex::UnlockShared() noexcept
	{	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasesrwlockshared
		ReleaseSRWLockShared(reinterpret_cast<PSRWLOCK>(&_Handle));
	}
}
#endif
