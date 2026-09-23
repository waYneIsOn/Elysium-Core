/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_DELEGATEAWAITER
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_AWAITER_DELEGATEAWAITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../../Container/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_TUPLE
#include "../../Container/Tuple.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_FORWARD
#include "../../Functional/Forward.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE
#include "../CoroutineHandle.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "../../TypeTraits/IsSame.hpp"
#endif

namespace Elysium::Core::Template::Coroutines::Awaiter
{
	/// <summary>
	/// An Awaiter (ie. a suspension object) which ...
	/// </summary>
	/// <typeparam name="Delegate"></typeparam>
	template <class Promise, class ReturnType, class ...Args>
	class DelegateAwaiter
	{
	public:
		constexpr DelegateAwaiter() noexcept = delete;

		inline constexpr DelegateAwaiter(const Elysium::Core::Template::Container::Delegate<ReturnType, Args...> Delegate, Args... Arguments) noexcept
			: _Delegate(Delegate), _Arguments(Elysium::Core::Template::Functional::Forward<Args>(Arguments)...)
		{ }

		constexpr DelegateAwaiter(const DelegateAwaiter& Source) noexcept = default;

		constexpr DelegateAwaiter(DelegateAwaiter&& Right) noexcept = default;

		constexpr ~DelegateAwaiter() noexcept = default;
	public:
		constexpr DelegateAwaiter& operator=(const DelegateAwaiter& Source) noexcept = default;

		constexpr DelegateAwaiter& operator=(DelegateAwaiter&& Right) noexcept = default;
	public:
		/// <summary>
		/// Can I continue right now?
		/// </summary>
		/// <returns></returns>
		inline constexpr bool await_ready() const noexcept
		{
			OutputDebugStringA("DelegateAwaiter::await_ready()\r\n");
			return _HasCalledDelegate;
		}

		/// <summary>
		/// If I cannot continue right now, what should happen to the current coroutine and who will resume it?
		/// </summary>
		/// <param name=""></param>
		inline constexpr bool await_suspend(Elysium::Core::Template::Coroutines::CoroutineHandle<Promise> Handle) noexcept
		{
			_Promise = &Handle.ToPromise();
			bool ManagedInternally = !_Promise->_ManagedExternally;

			OutputDebugStringA(ManagedInternally ? "DelegateAwaiter::await_suspend(...) -> managed INTERNALLY: RESUME right away\r\n" :
				"DelegateAwaiter::await_suspend(...) -> managed EXTERNALLY: SUSPEND\r\n");

			if constexpr (Elysium::Core::Template::TypeTraits::IsSameValue<void, ReturnType>)
			{
				_Delegate(_Arguments);
				_HasCalledDelegate = true;
			}
			else
			{
				auto Result = _Delegate(_Arguments);
				_HasCalledDelegate = true;

				// @ToDo
				bool sdf = false;
			}
			/*
			// coroutine can resume right away
			return false;
			*/
			/*
			// coroutine needs to remain suspended
			return true;
			*/
			
			// coroutine can resume right away (if managed internally) or needs to remain suspended (if managed externally).
			return !ManagedInternally;
		}

		/// <summary>
		/// What should I do once I resume execution?
		/// </summary>
		inline constexpr ReturnType await_resume() const noexcept
		{
			bool sdf = false;

			if constexpr (!Elysium::Core::Template::TypeTraits::IsSameValue<void, ReturnType>)
			{
				// @ToDo
				//return _Promise->_Result;
				return 0;
			}
		}
	private:
		Elysium::Core::Template::Container::Delegate<ReturnType, Args...> _Delegate;
		Elysium::Core::Template::Container::Tuple<Args...> _Arguments;

		bool _HasCalledDelegate{};

		Promise* _Promise{};
	};
}
#endif
