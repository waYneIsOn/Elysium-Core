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
			return _Task.GetIsCompleted();
		}

		inline constexpr bool await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<> OuterHandle) noexcept
		{
			_Task._Promise->_OuterCoroutineHandle = OuterHandle;

			// coroutine needs to remain suspended
			return true;
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
