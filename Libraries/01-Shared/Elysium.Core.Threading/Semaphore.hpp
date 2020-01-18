/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_SEMAPHORE
#define ELYSIUM_CORE_THREADING_SEMAPHORE

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Threading
{
	// Limits the number of threads that can access a resource or pool of resources concurrently.
	class ELYSIUM_CORE_API Semaphore final
	{
	public:
		Semaphore(const uint32_t InitialCount, const uint32_t MaximumCount);
		Semaphore(const Semaphore& Source) = delete;
		Semaphore(Semaphore&& Right) noexcept = delete;
		~Semaphore();

		Semaphore& operator=(const Semaphore& Source) = delete;
		Semaphore& operator=(Semaphore&& Right) noexcept = delete;

		const bool WaitOne();
		const int Release();
	private:
		ELYSIUM_SEMAPHORE_HANDLE _Handle;
	};
}
#endif
