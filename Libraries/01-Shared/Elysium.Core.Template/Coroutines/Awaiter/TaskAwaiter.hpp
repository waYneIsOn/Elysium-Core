/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_TASKAWAITER
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_TASKAWAITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINECONTINUATIONSTATE
#include "../CoroutineContinuationState.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../CoroutineHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "../../TypeTraits/IsSame.hpp"
#endif

namespace Elysium::Core::Template::Threading::Tasks
{
	template <class Result>
	class Task;
}

namespace Elysium::Core::Template::Coroutines::Awaiter
{
	template <class TaskResult>
	class TaskAwaiter
	{
	public:
		constexpr TaskAwaiter() noexcept = delete;

		inline constexpr TaskAwaiter(Elysium::Core::Template::Threading::Tasks::Task<TaskResult>& Task) noexcept
			: _Task(Task)
		{ }

		constexpr TaskAwaiter(const TaskAwaiter& Source) noexcept = default;

		constexpr TaskAwaiter(TaskAwaiter&& Right) noexcept = default;

		constexpr ~TaskAwaiter() noexcept = default;
	public:
		constexpr TaskAwaiter& operator=(const TaskAwaiter& Source) noexcept = default;

		constexpr TaskAwaiter& operator=(TaskAwaiter&& Right) noexcept = default;
	public:
		inline constexpr bool await_ready() const noexcept
		{
			return Elysium::Core::Template::Coroutines::CoroutineContinuationState::Completed ==
				_Task._Promise->_ContinuationState.Load(Elysium::Core::Template::Memory::MemoryOrder::Acquire);
		}

		inline constexpr bool await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<> OuterHandle) noexcept
		{
			// Publish the continuation BEFORE publishing Waiting
			_Task._Promise->_OuterCoroutineHandle = OuterHandle;

			Elysium::Core::Template::Coroutines::CoroutineContinuationState ExpectedTaskContinuationState = Elysium::Core::Template::Coroutines::CoroutineContinuationState::Pending;
			if (_Task._Promise->_ContinuationState.CompareExchangeStrong(ExpectedTaskContinuationState, Elysium::Core::Template::Coroutines::CoroutineContinuationState::Waiting,
				Elysium::Core::Template::Memory::MemoryOrder::Release, Elysium::Core::Template::Memory::MemoryOrder::Acquire))
			{	// Coroutine remains suspended
				return true;
			}

			// Completion won the race -> Coroutine can resume right away
			return false;

			/*
			if (_Task.GetIsCompleted())
			{	// coroutine can resume right away
				return false;
			}

			// coroutine needs to remain suspended
			return true;
			
			//return !await_ready();
			*/
		}
		
		inline constexpr TaskResult await_resume() const noexcept
		{
			if constexpr (!Elysium::Core::Template::TypeTraits::IsSameValue<void, TaskResult>)
			{
				return _Task.GetResult();
			}
		}
	private:
		Elysium::Core::Template::Threading::Tasks::Task<TaskResult>& _Task;
	};
}
#endif
