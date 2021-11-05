/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_SEMAPHORE
#define ELYSIUM_CORE_THREADING_SEMAPHORE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#include "WaitHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Threading
{
	// Limits the number of threads that can access a resource or pool of resources concurrently.
	class ELYSIUM_CORE_API Semaphore final : public WaitHandle
	{
	public:
		Semaphore(const uint32_t InitialCount, const uint32_t MaximumCount);

		Semaphore(const uint32_t InitialCount, const uint32_t MaximumCount, const String& Name);

		//Semaphore(const uint32_t InitialCount, const uint32_t MaximumCount, const String& Name, bool& CreatedNew);

		Semaphore(const Semaphore& Source) = delete;

		Semaphore(Semaphore&& Right) noexcept = delete;

		virtual ~Semaphore();
	public:
		Semaphore& operator=(const Semaphore& Source) = delete;

		Semaphore& operator=(Semaphore&& Right) noexcept = delete;
	public:
		const Elysium::Core::int32_t Release();
	};
}
#endif
