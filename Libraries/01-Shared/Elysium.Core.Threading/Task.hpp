/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_TASKS_TASK
#define ELYSIUM_CORE_THREADING_TASKS_TASK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ACTION
#include "../Elysium.Core.Template/Action.hpp"
#endif

#ifndef ELYSIUM_CORE_AGGREGATEEXCEPTION
#include "../Elysium.Core/AggregateException.hpp"
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_AUTORESETEVENT
#include "AutoResetEvent.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASKCREATIONOPTIONS
#include "TaskCreationOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_TASKS_TASKSTATUS
#include "TaskStatus.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "ThreadPool.hpp"
#endif

#ifndef _ATOMIC_
#include <atomic>
#endif

namespace Elysium::Core::Threading::Tasks
{
	class ELYSIUM_CORE_API Task final : public IAsyncResult
	{
	public:
		Task(const Elysium::Core::Template::Container::Action<>& Action);

		Task(const Task& Source) = delete;

		Task(Task&& Right) noexcept = delete;

		virtual ~Task();
	public:
		Task& operator=(const Task& Source) = delete;

		Task& operator=(Task&& Right) noexcept = delete;
	public:
		const Elysium::Core::int32_t GetId() const;

		const TaskCreationOptions GetCreationOptions() const;

		const TaskStatus GetStatus() const;

		const AggregateException* GetException() const;

		virtual const void* GetAsyncState() const override;

		virtual Elysium::Core::Threading::WaitHandle& GetAsyncWaitHandle() override;

		virtual const bool GetCompletedSynchronously() const override;

		virtual const bool GetIsCompleted() const override;

		const bool GetIsCanceled() const;

		const bool GetIsCompletedSuccessfully() const;

		const bool GetIsFaulted() const;
	public:
		void RunSynchronously();

		void Start();

		void Wait();
	private:
		inline static Elysium::Core::int32_t _TaskIdCounter = 0;

		const Elysium::Core::Template::Container::Action<> _Action;
		const Elysium::Core::int32_t _Id;
		const TaskCreationOptions _CreationOptions;
		AutoResetEvent _WaitEvent;

		std::atomic<TaskStatus> _Status;
		std::atomic<AggregateException*> _Exception;

#if defined ELYSIUM_CORE_OS_WINDOWS
		const ELYSIUM_TASK_HANDLE _Handle;

		static void Callback(ELYSIUM_TASK_CALLBACK_INSTANCE Instance, void* Context, ELYSIUM_TASK_HANDLE Work); 
#else
#error "unsupported os"
#endif
	};
}
#endif
