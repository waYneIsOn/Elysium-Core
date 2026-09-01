/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_SUSPENDNEVER
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_SUSPENDNEVER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../CoroutineHandle.hpp"
#endif

namespace Elysium::Core::Template::Coroutines::Awaiter
{
	/// <summary>
	/// An Awaiter (ie. a suspension object) which doesn't suspend at all and should be used for "already-completed" operations.
	/// </summary>
	class SuspendNever
	{
	public:
		constexpr SuspendNever() noexcept = default;

		constexpr SuspendNever(const SuspendNever& Source) noexcept = default;

		constexpr SuspendNever(SuspendNever&& Right) noexcept = default;

		constexpr ~SuspendNever() noexcept = default;
	public:
		constexpr SuspendNever& operator=(const SuspendNever& Source) noexcept = default;

		constexpr SuspendNever& operator=(SuspendNever&& Right) noexcept = default;
	public:
		inline constexpr bool await_ready() const noexcept
		{
			return true;
		}

		inline constexpr void await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<>) const noexcept
		{ }

		inline constexpr void await_resume() const noexcept
		{ }
	};
}
#endif
