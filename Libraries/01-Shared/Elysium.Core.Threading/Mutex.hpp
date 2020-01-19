/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_MUTEX
#define ELYSIUM_CORE_THREADING_MUTEX

#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Threading
{
	// A synchronization primitive that can also be used for interprocess synchronization.
	class ELYSIUM_CORE_API Mutex final //: public WaitHandle
	{
	public:
		Mutex();
		//Mutex(const bool InitiallyOwned);
		//Mutex(const bool InitiallyOwned, const String& Name, bool& CreatedNew);
		Mutex(const Mutex& Source) = delete;
		Mutex(Mutex&& Right) noexcept = delete;
		~Mutex();

		Mutex& operator=(const Mutex& Source) = delete;
		Mutex& operator=(Mutex&& Right) noexcept = delete;

		//virtual const bool WaitOne(const int32_t MillisecondsTimeout, const bool ExitContext) override;

		const bool WaitOne();
		void ReleaseMutex();
	private:
		ELYSIUM_MUTEX_HANDLE _Handle;
	};
}
#endif
