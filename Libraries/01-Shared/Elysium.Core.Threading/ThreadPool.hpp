/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_INTERNAL_OSTHREADPOOL
#include "OSThreadPool.hpp"
#endif

namespace Elysium::Core::IO
{
	class FileStream;
	class FileSystemWatcher;
}

namespace Elysium::Core::Net::Sockets
{
	class Socket;
}

namespace Elysium::Core::Threading::Tasks
{
	class Task;
}

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API ThreadPool final
	{
		friend class Elysium::Core::IO::FileStream;
		friend class Elysium::Core::IO::FileSystemWatcher;
		friend class Elysium::Core::Net::Sockets::Socket;
		friend class Elysium::Core::Threading::Tasks::Task;
	public:
		ThreadPool() = delete;
		ThreadPool(const ThreadPool& Source) = delete;
		ThreadPool(ThreadPool&& Right) noexcept = delete;
		~ThreadPool() = delete;

		ThreadPool& operator=(const ThreadPool& Source) = delete;
		ThreadPool& operator=(ThreadPool&& Right) noexcept = delete;
		/*
		static const Elysium::Core::uint64_t GetCompletedWorkItemCount();
		static const Elysium::Core::uint64_t GetPendingWorkItemCount();
		static const Elysium::Core::uint32_t GetThreadCount();
		*/
		static void GetAvailableThreads(Elysium::Core::uint32_t& WorkerThreads, Elysium::Core::uint32_t& CompletionPortThreads);
		static void GetMaxThreads(Elysium::Core::uint32_t& WorkerThreads, Elysium::Core::uint32_t& CompletionPortThreads);
		static void GetMinThreads(Elysium::Core::uint32_t& WorkerThreads, Elysium::Core::uint32_t& CompletionPortThreads);

		static const bool SetMaxThreads(const Elysium::Core::uint32_t WorkerThreads, const Elysium::Core::uint32_t CompletionPortThreads);
		static const bool SetMinThreads(const Elysium::Core::uint32_t WorkerThreads, const Elysium::Core::uint32_t CompletionPortThreads);
	private:
#pragma warning (disable: 4251)	// Internal::OSThreadPool won't be used outside ThreadPool
		inline static Internal::OSThreadPool _WorkerPool = Internal::OSThreadPool(Elysium::Core::Environment::ProcessorCount(), Elysium::Core::Environment::ProcessorCount() * 128 - 1);
		inline static Internal::OSThreadPool _IOPool = Internal::OSThreadPool(Elysium::Core::Environment::ProcessorCount(), 1000);
#pragma warning (default: 4251)
	};
}
#endif
