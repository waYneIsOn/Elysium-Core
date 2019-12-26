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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREAD
#include "Thread.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API ThreadPool final
	{
	public:
		ThreadPool(const ThreadPool& Source) = delete;
		ThreadPool(TimeSpan&& Right) noexcept = delete;
		~ThreadPool();

		ThreadPool& operator=(const ThreadPool& Source) = delete;
		ThreadPool& operator=(ThreadPool&& Right) noexcept = delete;

		static const ThreadPool& GetThreadPool();
	private:
		ThreadPool();

		//Elysium::Core::Collections::Template::List<Thread> _WorkerThreads;
		//Elysium::Core::Collections::Template::List<Thread> _IOThreads;

		void RunWorker();
		void RunIO();

		static const ThreadPool _Instance;
	};
}
#endif
