/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#define ELYSIUM_CORE_THREADING_TASKS_TASK

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASKCREATIONOPTIONS
#include "TaskCreationOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASKSTATUS
#include "TaskStatus.hpp"
#endif

#ifndef ELYSIUM_CORE_AGGREGATEEXCEPTION
#include "../Elysium.Core/AggregateException.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "ThreadPool.hpp"
#endif

namespace Elysium::Core::Threading::Tasks
{
	class ELYSIUM_CORE_API Task final
	{
	public:
		Task(const Delegate<void> Action);
		Task(const Task& Source) = delete;
		Task(Task&& Right) noexcept = delete;
		~Task();

		Task& operator=(const Task& Source) = delete;
		Task& operator=(Task&& Right) noexcept = delete;

		const int32_t GetId() const;
		const TaskCreationOptions GetCreationOptions() const;
		const TaskStatus GetStatus() const;
		const AggregateException* GetException() const;

		const bool GetIsCanceled() const;
		const bool GetIsCompleted() const;
		const bool GetIsCompletedSuccessfully() const;
		const bool GetIsFaulted() const;
		
		void RunSynchronously();
		void Start(ThreadPool& ThreadPool);
		void Wait();
	private:
		const int32_t _Id;
		const Delegate<void> _Action;
		const TaskCreationOptions _CreationOptions;

		std::atomic<TaskStatus> _Status;
		std::atomic<AggregateException*> _Exception;

		static int32_t _TaskIdCounter;
	};
}
#endif
