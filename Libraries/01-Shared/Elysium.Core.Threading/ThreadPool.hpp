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

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
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
		ThreadPool(const size_t NumberOfThreads);
		ThreadPool(const ThreadPool& Source) = delete;
		ThreadPool(ThreadPool&& Right) noexcept = delete;
		~ThreadPool();

		ThreadPool& operator=(const ThreadPool& Source) = delete;
		ThreadPool& operator=(ThreadPool&& Right) noexcept = delete;

		const size_t GetNumberOfThreads() const;

		void Start();
		void Stop();
	private:
		const Elysium::Core::Collections::Template::Array<ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE> _ThreadHandles;

		std::atomic<bool> _ShouldStop;
		std::atomic<bool> _IsRunning;

		void Run();
	};
}
#endif
