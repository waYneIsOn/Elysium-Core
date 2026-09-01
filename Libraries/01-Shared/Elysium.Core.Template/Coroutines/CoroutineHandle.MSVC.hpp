/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE_MSVC
#define ELYSIUM_CORE_TEMPLATE_COROUTINES_COROUTINEHANDLE_MSVC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../System/Compiler.hpp"
#endif

#ifndef _COROUTINE_
#include <coroutine>
#endif

namespace Elysium::Core::Template::Coroutines
{
#if defined ELYSIUM_CORE_COMPILER_MSVC
	template<class = void>
	class CoroutineHandle;

	template <>
	class CoroutineHandle<void>
	{
	public:
		constexpr CoroutineHandle() noexcept = default;

		template <class Promise>
		inline constexpr CoroutineHandle(std::coroutine_handle<Promise> CoHandle) noexcept
			: _Handle(CoHandle.address())
		{ }

		constexpr CoroutineHandle(const CoroutineHandle& Source) noexcept = default;

		constexpr CoroutineHandle(CoroutineHandle&& Right) noexcept = default;

		constexpr ~CoroutineHandle() noexcept = default;
	public:
		constexpr CoroutineHandle& operator=(const CoroutineHandle& Source) noexcept = default;

		constexpr CoroutineHandle& operator=(CoroutineHandle&& Right) noexcept = default;
	public:
		inline constexpr explicit operator bool() const noexcept
		{
			return _Handle != nullptr;
		}

		inline void operator()() const
		{
			__builtin_coro_resume(_Handle);
		}
	public:
		inline constexpr const void* address() const noexcept
		{
			return _Handle;
		}

		inline bool done() const noexcept
		{
			return __builtin_coro_done(_Handle);
		}
	public:
		void resume() const
		{
			__builtin_coro_resume(_Handle);
		}

		void destroy() const noexcept
		{
			__builtin_coro_destroy(_Handle);
		}
	private:
		void* _Handle{};
	};

	template <class Promise>
	class CoroutineHandle
	{
	public:
		constexpr CoroutineHandle() noexcept = default;

		inline constexpr CoroutineHandle(std::coroutine_handle<Promise> CoHandle) noexcept
			: _Handle(CoHandle.address())
		{ }

		constexpr CoroutineHandle(const CoroutineHandle& Source) noexcept = default;

		constexpr CoroutineHandle(CoroutineHandle&& Right) noexcept = default;

		constexpr ~CoroutineHandle() noexcept = default;
	public:
		constexpr CoroutineHandle& operator=(const CoroutineHandle& Source) noexcept = default;

		constexpr CoroutineHandle& operator=(CoroutineHandle&& Right) noexcept = default;
	public:
		inline static CoroutineHandle FromPromise(Promise& Value) noexcept 
		{
			void* AddressOfPromise = const_cast<void*>(static_cast<const volatile void*>(std::addressof(Value)));
			void* AddressOfCoroutineFrame = __builtin_coro_promise(AddressOfPromise, 0, true);

			CoroutineHandle _Result{};
			_Result._Handle = AddressOfCoroutineFrame;

			return _Result;
		}
	public:
		inline Promise& ToPromise() const noexcept
		{
			return *static_cast<Promise*>(__builtin_coro_promise(_Handle, 0, false));
		}
	public:
		inline constexpr explicit operator bool() const noexcept
		{
			return _Handle != nullptr;
		}
	public:
		inline void operator()() const
		{
			__builtin_coro_resume(_Handle);
		}
	public:
		inline constexpr const void* address() const noexcept
		{
			return _Handle;
		}

		inline bool done() const noexcept
		{
			return __builtin_coro_done(_Handle);
		}
	public:
		void resume() const
		{
			__builtin_coro_resume(_Handle);
		}

		void destroy() const noexcept
		{
			__builtin_coro_destroy(_Handle);
		}
	private:
		void* _Handle{};
	};
#endif
}
#endif
