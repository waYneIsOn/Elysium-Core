/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#define ELYSIUM_CORE_THREADING_THREADPOOL

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREAD
#include "Thread.hpp"
#endif

#ifndef _ATOMIC_
#include <atomic>
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API ThreadPool final
	{
	public:
		ThreadPool();
		ThreadPool(const size_t NumberOfWorkerThreads, const size_t NumberOfIOThreads);
		ThreadPool(const ThreadPool& Source) = delete;
		ThreadPool(TimeSpan&& Right) noexcept = delete;
		~ThreadPool();

		ThreadPool& operator=(const ThreadPool& Source) = delete;
		ThreadPool& operator=(ThreadPool&& Right) noexcept = delete;

		void Start();
		void Stop();
	private:
		const Elysium::Core::Collections::Template::Array<Thread> _WorkerThreads;
		const Elysium::Core::Collections::Template::Array<Thread> _IOThreads;

		std::atomic<bool> _ShouldStop;
		std::atomic<bool> _IsRunning;

		void RunWorker();
		void RunIO();
	};
}
#endif
