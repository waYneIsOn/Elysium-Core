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
	class FinalAwaiter
	{
	public:
		constexpr FinalAwaiter() noexcept = delete;
		
		inline constexpr FinalAwaiter(Elysium::Core::Template::Coroutines::CoroutineHandle<> ContinuationHandle) noexcept
			: _ContinuationHandle(ContinuationHandle)
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
			//OutputDebugStringA("FinalAwaiter::await_ready()\r\n");
			return false;
		}

		inline constexpr std::coroutine_handle<> await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<> CompletedHandle) noexcept
		{
			/*
			static const std::type_info& NoOperationTypeId = 
				typeid(Elysium::Core::Template::Coroutines::CoroutineHandle<Elysium::Core::Template::Coroutines::NoOperationCoroutinePromise>);
			const std::type_info& ThisTypeId = typeid(_ContinuationHandle);

			if (NoOperationTypeId.hash_code() == ThisTypeId.hash_code())
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
			return _ContinuationHandle;
		}

		inline constexpr void await_resume() const noexcept
		{ }
	private:
		Elysium::Core::Template::Coroutines::CoroutineHandle<> _ContinuationHandle;
	};
}
#endif
