/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_THREADPOOLWORKQUEUE
#define ELYSIUM_CORE_THREADING_THREADPOOLWORKQUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_CRITICALSECTION
#include "CriticalSection.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_AUTORESETEVENT
#include "AutoResetEvent.hpp"
#endif

namespace Elysium::Core::Threading
{
	/*
	namespace Tasks
	{
		class Task;
	}

	class ThreadPoolWorkQueue final
	{
		friend class ThreadPool;
	public:
		ThreadPoolWorkQueue();
		ThreadPoolWorkQueue(const ThreadPoolWorkQueue& Source) = delete;
		ThreadPoolWorkQueue(ThreadPoolWorkQueue&& Right) noexcept = delete;
		~ThreadPoolWorkQueue();

		ThreadPoolWorkQueue& operator=(const ThreadPoolWorkQueue& Source) = delete;
		ThreadPoolWorkQueue& operator=(ThreadPoolWorkQueue&& Right) noexcept = delete;

		void Submit(Elysium::Core::Threading::Tasks::Task& Task);
		Tasks::Task* GetNextTask();
	private:
		CriticalSection _CriticalSection;
		Elysium::Core::Collections::Template::Queue<Tasks::Task*> _Queue;

		AutoResetEvent _WorkAvailable;
	};
	*/
}
#endif
