/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_FINALAWAITER
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_FINALAWAITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../CoroutineHandle.hpp"
#endif

namespace Elysium::Core::Template::Coroutines::Awaiter
{
	template <class PromiseType>
	class FinalAwaiter
	{
	public:
		constexpr FinalAwaiter() noexcept = delete;
		
		inline constexpr FinalAwaiter(PromiseType& Promise, Elysium::Core::Template::Coroutines::CoroutineHandle<> ContinuationHandle) noexcept
			: _Promise(Promise), _ContinuationHandle(ContinuationHandle)
		{ }
		
		constexpr FinalAwaiter(const FinalAwaiter& Source) noexcept = default;

		constexpr FinalAwaiter(FinalAwaiter&& Right) noexcept = default;

		constexpr ~FinalAwaiter() noexcept = default;
	public:
		constexpr FinalAwaiter& operator=(const FinalAwaiter& Source) noexcept = default;

		constexpr FinalAwaiter& operator=(FinalAwaiter&& Right) noexcept = default;
	public:
		inline constexpr bool await_ready() const noexcept
		{
			return false;
		}

		inline constexpr std::coroutine_handle<> await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<> CompletedHandle) noexcept
		{
			/*
			if (Elysium::Core::Template::Coroutines::CoroutineHandle<Elysium::Core::Template::Coroutines::NoOperationCoroutinePromise>::_DefaultHandle == _ContinuationHandle._Handle)
			{
				OutputDebugStringA("FinalAwaiter::await_suspend(...) -> coroutine yields to NOOP_COROUTINE\r\n");
			}
			else if (_ContinuationHandle)
			{
				OutputDebugStringA("FinalAwaiter::await_suspend(...) -> coroutine yields to OUTER\r\n");
			}
			else
			{
				OutputDebugStringA("FinalAwaiter::await_suspend(...) -> coroutine yields to NOTHING\r\n");
			}
			*/
			if (_Promise._OuterCoroutineHandle)
			{
				// parent owns us, ergo don't signal completion event
				return _ContinuationHandle;

				//return static_cast<std::coroutine_handle<>>(_Promise._OuterCoroutineHandle);
			}

			_Promise._CoroutineCompletionEvent.Set();

			// Wait() path: just stay suspended
			return Elysium::Core::Template::Coroutines::CoroutineHandle<Elysium::Core::Template::Coroutines::NoOperationCoroutinePromise>{};
		}

		inline constexpr void await_resume() const noexcept
		{ }
	private:
		PromiseType& _Promise;
		Elysium::Core::Template::Coroutines::CoroutineHandle<> _ContinuationHandle;
	};
}
#endif
