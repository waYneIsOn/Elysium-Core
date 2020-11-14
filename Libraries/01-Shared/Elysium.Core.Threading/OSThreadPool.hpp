/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_INTERNAL_OSTHREADPOOL
#define ELYSIUM_CORE_THREADING_INTERNAL_OSTHREADPOOL

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

namespace Elysium::Core::Net::Sockets
{
	class Socket;
}

namespace Elysium::Core::Threading::Tasks
{
	class Task;
}

namespace Elysium::Core::Threading::Internal
{
	class OSThreadPool final
	{
		friend class Elysium::Core::Net::Sockets::Socket;
		friend class Elysium::Core::Threading::Tasks::Task;
	public:
		OSThreadPool(const Elysium::Core::uint32_t Minimum, const Elysium::Core::uint32_t Maximum);
		OSThreadPool(const OSThreadPool& Source) = delete;
		OSThreadPool(OSThreadPool&& Right) noexcept = delete;
		~OSThreadPool();

		OSThreadPool& operator=(const OSThreadPool& Source) = delete;
		OSThreadPool& operator=(OSThreadPool&& Right) noexcept = delete;
		/*
		const Elysium::Core::uint64_t GetCompletedWorkItemCount() const;
		const Elysium::Core::uint64_t GetPendingWorkItemCount() const;
		const Elysium::Core::uint32_t GetThreadCount() const;
		*/
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
