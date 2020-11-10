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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOLWORKQUEUE
#include "ThreadPoolWorkQueue.hpp"
#endif

#ifndef _ATOMIC_
#include <atomic>
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "../Elysium.Core.Net/Socket.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API ThreadPool final
	{
		friend class Tasks::Task;
	public:
		ThreadPool(const bool IsIOPool);
		ThreadPool(const size_t NumberOfThreads, const bool IsIOPool);
		ThreadPool(const ThreadPool& Source) = delete;
		ThreadPool(ThreadPool&& Right) noexcept = delete;
		~ThreadPool();

		ThreadPool& operator=(const ThreadPool& Source) = delete;
		ThreadPool& operator=(ThreadPool&& Right) noexcept = delete;

		const size_t GetNumberOfThreads() const;

		void Start();
		void Stop();

		const bool BindIOCompletionCallback(const Elysium::Core::Net::Sockets::Socket& Socket);
	private:
		const bool _IsIOPool;
		ELYSIUM_IOCOMPLETIONPORT_HANDLE _SomeSocketIOCompletionPortHandle;

		const Elysium::Core::Collections::Template::Array<unsigned long> _Ids;
		const Elysium::Core::Collections::Template::Array<ELYSIUM_SYNCHRONIZATION_PRIMITIVE_HANDLE> _ThreadHandles;

		ThreadPoolWorkQueue _WorkQueue;

		std::atomic<bool> _ShouldStop;
		std::atomic<bool> _IsRunning;

		static void WorkerThreadMain(ThreadPool& ThreadPool);

		static void IOThreadMain(ThreadPool& ThreadPool);

		const bool BindIOCompletionCallback(const ELYSIUM_IOCOMPLETIONPORT_HANDLE IOCompletionPortHandle);
	};
}
#endif
