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

#ifndef _STDINT
#include <cstdint>
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
	private:
		const uint32_t _Count;
		const uint32_t _MaximumCount;
	};
}
#endif
