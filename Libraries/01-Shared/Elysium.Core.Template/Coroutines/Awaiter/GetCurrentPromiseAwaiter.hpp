/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_GETCURRENTPROMISEAWAITER
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_GETCURRENTPROMISEAWAITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../CoroutineHandle.hpp"
#endif

namespace Elysium::Core::Template::Coroutines::Awaiter
{
	/// <summary>
	/// An Awaiter (ie. a suspension object) which always suspends and and captures the current coroutine frame's promise.
	/// </summary>
	/// <typeparam name="Promise"></typeparam>
	template <class Promise>
	class GetCurrentPromiseAwaiter
	{
	public:
		constexpr GetCurrentPromiseAwaiter() noexcept = default;

		constexpr GetCurrentPromiseAwaiter(const GetCurrentPromiseAwaiter& Source) noexcept = default;

		constexpr GetCurrentPromiseAwaiter(GetCurrentPromiseAwaiter&& Right) noexcept = default;

		constexpr ~GetCurrentPromiseAwaiter() noexcept = default;
	public:
		constexpr GetCurrentPromiseAwaiter& operator=(const GetCurrentPromiseAwaiter& Source) noexcept = default;

		constexpr GetCurrentPromiseAwaiter& operator=(GetCurrentPromiseAwaiter&& Right) noexcept = default;
	public:
		inline constexpr bool await_ready() const noexcept
		{
			return false;
		}

		inline constexpr bool await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<Promise> Handle) noexcept
		{
			_Promise = &Handle.ToPromise();

			// immediately continue the coroutine
			return false;
		}

		inline constexpr Promise& await_resume() const noexcept
		{
			return *_Promise;
		}
	private:
		Promise* _Promise{};
	};
}
#endif
