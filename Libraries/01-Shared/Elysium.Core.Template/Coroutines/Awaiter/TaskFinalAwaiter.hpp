/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_TASKFINALAWAITER
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_TASKFINALAWAITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../CoroutineHandle.hpp"
#endif

namespace Elysium::Core::Template::Coroutines::Awaiter
{
	class TaskFinalAwaiter
	{
	public:
		constexpr TaskFinalAwaiter() noexcept = delete;
		
		inline constexpr TaskFinalAwaiter(Elysium::Core::Template::Coroutines::CoroutineHandle<> ContinuationHandle) noexcept
			: _ContinuationHandle(ContinuationHandle)
		{ }
		
		constexpr TaskFinalAwaiter(const TaskFinalAwaiter& Source) noexcept = default;

		constexpr TaskFinalAwaiter(TaskFinalAwaiter&& Right) noexcept = default;

		constexpr ~TaskFinalAwaiter() noexcept = default;
	public:
		constexpr TaskFinalAwaiter& operator=(const TaskFinalAwaiter& Source) noexcept = default;

		constexpr TaskFinalAwaiter& operator=(TaskFinalAwaiter&& Right) noexcept = default;
	public:
		inline constexpr bool await_ready() const noexcept
		{
			return false;
		}

		inline constexpr std::coroutine_handle<> await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<> CompletedHandle) noexcept
		{
			if (_ContinuationHandle)
			{
				bool sdfsdf = false;
			}

			return _ContinuationHandle ? _ContinuationHandle : std::noop_coroutine();
		}

		inline constexpr void await_resume() const noexcept
		{ }
	private:
		Elysium::Core::Template::Coroutines::CoroutineHandle<> _ContinuationHandle;
	};
}
#endif
