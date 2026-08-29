/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_SUSPENDALWAYS
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_SUSPENDALWAYS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "CoroutineHandle.hpp"
#endif

namespace Elysium::Core::Template::Coroutines
{
	class SuspendAlways
	{
	public:
		constexpr SuspendAlways() noexcept = default;

		constexpr SuspendAlways(const SuspendAlways& Source) noexcept = default;

		constexpr SuspendAlways(SuspendAlways&& Right) noexcept = default;

		constexpr ~SuspendAlways() noexcept = default;
	public:
		constexpr SuspendAlways& operator=(const SuspendAlways& Source) noexcept = default;

		constexpr SuspendAlways& operator=(SuspendAlways&& Right) noexcept = default;
	public:
		inline constexpr bool await_ready() const noexcept
		{
			return false;
		}

		inline constexpr void await_suspend(CoroutineHandle<>) const noexcept
		{ }

		inline constexpr void await_resume() const noexcept
		{ }
	};
}
#endif
