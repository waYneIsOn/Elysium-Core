/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_DELAYFOR
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_DELAYFOR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DURATION
#include "../../Chrono/Duration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../CoroutineHandle.hpp"
#endif

namespace Elysium::Core::Template::Coroutines::Awaiter
{
	/// <summary>
	/// An Awaiter (ie. a suspension object) which suspends for a given timeframe delaying its execution.
	/// </summary>
	class DelayFor
	{
	public:
		constexpr DelayFor() noexcept = default;

		constexpr DelayFor(const DelayFor& Source) noexcept = default;

		constexpr DelayFor(DelayFor&& Right) noexcept = default;

		constexpr ~DelayFor() noexcept = default;
	public:
		constexpr DelayFor& operator=(const DelayFor& Source) noexcept = default;

		constexpr DelayFor& operator=(DelayFor&& Right) noexcept = default;
	public:
		/// <summary>
		/// Can I continue right now?
		/// </summary>
		/// <returns></returns>
		inline constexpr bool await_ready() const noexcept
		{
			return _Duration <= 0;
		}

		/// <summary>
		/// If I cannot continue right now, what should happen to the current coroutine and who will resume it?
		/// </summary>
		/// <param name=""></param>
		inline constexpr void await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<>) const noexcept
		{
			// @ToDo: timer scheduling!
			throw 1;
		}

		/// <summary>
		/// What should I do once I resume execution?
		/// </summary>
		inline constexpr void await_resume() const noexcept
		{ }
	private:
		Elysium::Core::Template::Chrono::MilliSeconds _Duration{};
	};
}
#endif
