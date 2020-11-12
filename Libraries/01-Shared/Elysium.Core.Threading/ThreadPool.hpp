/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#define ELYSIUM_CORE_THREADING_THREADPOOL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_INTERNAL_INTERNALTHREADPOOL
#include "InternalThreadPool.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API ThreadPool final
	{
	public:
		ThreadPool() = delete;
		ThreadPool(const ThreadPool& Source) = delete;
		ThreadPool(ThreadPool&& Right) noexcept = delete;
		~ThreadPool() = delete;

		ThreadPool& operator=(const ThreadPool& Source) = delete;
		ThreadPool& operator=(ThreadPool&& Right) noexcept = delete;

		static void GetAvailableThreads(Elysium::Core::uint32_t& WorkerThreads, Elysium::Core::uint32_t& CompletionPortThreads);
		static void GetMaxThreads(Elysium::Core::uint32_t& WorkerThreads, Elysium::Core::uint32_t& CompletionPortThreads);
		static void GetMinThreads(Elysium::Core::uint32_t& WorkerThreads, Elysium::Core::uint32_t& CompletionPortThreads);

		static const bool SetMaxThreads(const Elysium::Core::uint32_t WorkerThreads, const Elysium::Core::uint32_t CompletionPortThreads);
		static const bool SetMinThreads(const Elysium::Core::uint32_t WorkerThreads, const Elysium::Core::uint32_t CompletionPortThreads);
	private:
		static Internal::InternalThreadPool _WorkerPool;
		static Internal::InternalThreadPool _IOPool;
	};
}
#endif
