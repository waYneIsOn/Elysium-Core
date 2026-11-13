/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASKSCHEDULER
#define ELYSIUM_CORE_TEMPLATE_THREADING_TASKS_TASKSCHEDULER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP
#include "../../Container/UnorderedMap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL
#include "../ThreadPool.hpp"
#endif





#ifndef __ATLCHECKED_H__
#include <atlchecked.h>
#endif

#ifndef _INTTYPES
#include <inttypes.h>
#endif




namespace Elysium::Core::Template::Threading::Tasks
{
	class TaskScheduler
	{
	protected:
		constexpr TaskScheduler() noexcept = default;
	public:
		constexpr TaskScheduler(const TaskScheduler& Source) noexcept = delete;

		constexpr TaskScheduler(TaskScheduler&& Right) noexcept = delete;

		~TaskScheduler() noexcept = default;
	public:
		constexpr TaskScheduler& operator=(const TaskScheduler& Source) noexcept = delete;

		constexpr TaskScheduler& operator=(TaskScheduler&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::System::size GetId() const noexcept
		{
			return _Id;
		}
	public:
		inline static TaskScheduler& GetDefault()
		{	// @ToDo
			static TaskScheduler DefaultScheduler{};
			return DefaultScheduler;
		}

		inline static TaskScheduler& GetCurrent()
		{	// @ToDo
			static TaskScheduler CurrentScheduler{};
			return CurrentScheduler;
		}
	public:
		template <class TaskResult>
		inline void QueueTask(Task<TaskResult>& Task)
		{
			// ...
		}

		template <class TaskResult>
		inline bool TryDequeue(Task<TaskResult>& Task)
		{
			/*
			typename Elysium::Core::Template::Threading::Tasks::Task<TaskResult>::PromiseType& Promise = Task._Promise;
			const char* TaskName = &Promise._Name[0];
			void* AddressOfPromise = &Promise;
			void* AddressOfHandle = &Task._CoroutineFrameHandle;
			/*
			char IdBuffer[32]{};
			snprintf(IdBuffer, sizeof(IdBuffer), "[task %" PRIu64 "]", Task._Id);
			*-/
			char AddressOfPromiseText[64]{};
			snprintf(AddressOfPromiseText, sizeof(AddressOfPromiseText), "%p", AddressOfPromise);

			char AddressOfHandleText[64]{};
			snprintf(AddressOfHandleText, sizeof(AddressOfHandleText), "%p", AddressOfHandle);

			char buffer[1024]{};
			strcat_s(buffer, "dequeuing task (destroying coroutine frame handle) \"");
			strcat_s(buffer, TaskName);
			strcat_s(buffer, "\" (Id: ");
			//strcat_s(buffer, sizeof(buffer), IdBuffer);
			strcat_s(buffer, ") with Promise ");
			strcat_s(buffer, sizeof(buffer), AddressOfPromiseText);
			strcat_s(buffer, " and CoroutineFrameHandle ");
			strcat_s(buffer, sizeof(buffer), AddressOfHandleText);
			strcat_s(buffer, "\r\n");

			OutputDebugStringA(buffer);
			*/
			Task._CoroutineFrameHandle.destroy();

			//OutputDebugStringA(buffer);

			return false;
		}
	private:
		Elysium::Core::Template::System::size _Id{};

		//Elysium::Core::Template::Container::UnorderedMap<void*, 

		//Elysium::Core::Template::Threading::ThreadPool::InternalThreadPool& _sdf;
		//Elysium::Core::Template::Threading::ThreadPool::GetIOPool();
		//Elysium::Core::Template::Threading::ThreadPool::GetWorkerPool();
	};
}
#endif
