/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_INTERNAL_INTERNALTHREADPOOL
#define ELYSIUM_CORE_THREADING_INTERNAL_INTERNALTHREADPOOL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Threading::Internal
{
	class InternalThreadPool final
	{
	public:
		InternalThreadPool(const Elysium::Core::uint32_t Minimum, const Elysium::Core::uint32_t Maximum);
		InternalThreadPool(const InternalThreadPool& Source) = delete;
		InternalThreadPool(InternalThreadPool&& Right) noexcept = delete;
		~InternalThreadPool();

		InternalThreadPool& operator=(const InternalThreadPool& Source) = delete;
		InternalThreadPool& operator=(InternalThreadPool&& Right) noexcept = delete;

		void GetAvailableThreads(Elysium::Core::uint32_t& Threads) const;
		void GetMaxThreads(Elysium::Core::uint32_t& Threads) const;
		void GetMinThreads(Elysium::Core::uint32_t& Threads) const;

		const bool SetMaxThreads(const Elysium::Core::uint32_t Threads);

		const bool SetMinThreads(const Elysium::Core::uint32_t Threads);
	private:
		ELYSIUM_THREADPOOL_HANDLE _Handle;
		ELYSIUM_THREADPOOL_ENVIRONMENT _Environment;
		ELYSIUM_THREADPOOL_CLEANUPGROUP_HANDLE _CleanupGroup;

		// ToDo: do we really need to keep track of those?
		Elysium::Core::uint32_t _MaxThreads;
		Elysium::Core::uint32_t _MinThreads;
	};
}
#endif
