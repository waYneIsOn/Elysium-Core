/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL_WINDOWS
#define ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL_WINDOWS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGRAL
#include "../Concepts/Integral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#include "_AtomicBase.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// 
	/// https://learn.microsoft.com/en-us/windows/win32/sync/interlocked-variable-access
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T, Elysium::Core::Template::System::size SizeOfT = sizeof(T)>
	class _AtomicIntegral;

	template <class T>
	class _AtomicIntegral<T, 1>
		: public _AtomicBase<T, 1>
	{
	public:
		constexpr _AtomicIntegral() noexcept = default;

		inline constexpr _AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
			: _AtomicBase<T, 1>(Value)
		{ }

		constexpr _AtomicIntegral(const _AtomicIntegral& Source) = delete;

		constexpr _AtomicIntegral(_AtomicIntegral&& Right) noexcept = delete;

		constexpr ~_AtomicIntegral() = default;
	public:
		inline T operator++() noexcept
		{
			return static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), 1));
		}

		inline T operator++(Elysium::Core::Template::System::int32_t) noexcept
		{
			T Result = static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), 1));
			--Result;
			return static_cast<T>(Result);
		}

		inline T operator--() noexcept
		{
			return static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), -1));
		}

		inline T operator--(Elysium::Core::Template::System::int32_t) noexcept
		{
			T Result = static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), -1));
			++Result;
			return static_cast<T>(Result);
		}

		// @ToDo
	};

	template <class T>
	class _AtomicIntegral<T, 2>
		: public _AtomicBase<T, 2>
	{
	public:
		constexpr _AtomicIntegral() noexcept = default;

		inline constexpr _AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
			: _AtomicBase<T, 2>(Value)
		{ }

		constexpr _AtomicIntegral(const _AtomicIntegral& Source) = delete;

		constexpr _AtomicIntegral(_AtomicIntegral&& Right) noexcept = delete;

		constexpr ~_AtomicIntegral() = default;
	public:
		inline T operator++() noexcept
		{
			return static_cast<T>(_InterlockedIncrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
		}

		inline T operator++(Elysium::Core::Template::System::int32_t) noexcept
		{
			T Result = static_cast<T>(_InterlockedIncrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
			--Result;
			return static_cast<T>(Result);
		}

		inline T operator--() noexcept
		{
			return static_cast<T>(_InterlockedDecrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
		}

		inline T operator--(Elysium::Core::Template::System::int32_t) noexcept
		{
			T Result = static_cast<T>(_InterlockedDecrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
			++Result;
			return static_cast<T>(Result);
		}

		// @ToDo
	};

	template <class T>
	class _AtomicIntegral<T, 4>
		: public _AtomicBase<T, 4>
	{
	public:
		constexpr _AtomicIntegral() noexcept = default;

		inline constexpr _AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept 
			: _AtomicBase<T, 4>(Value)
		{ }

		constexpr _AtomicIntegral(const _AtomicIntegral& Source) = delete;

		constexpr _AtomicIntegral(_AtomicIntegral&& Right) noexcept = delete;

		constexpr ~_AtomicIntegral() = default;
	public:
		inline T operator++() noexcept
		{
			return static_cast<T>(_InterlockedIncrement(&reinterpret_cast<volatile long&>(this->_Value)));
		}

		inline T operator++(Elysium::Core::Template::System::int32_t) noexcept
		{
			T Result = static_cast<T>(_InterlockedIncrement(&reinterpret_cast<volatile long&>(this->_Value)));
			--Result;
			return static_cast<T>(Result);
		}

		inline T operator--() noexcept
		{
			return static_cast<T>(_InterlockedDecrement(&reinterpret_cast<volatile long&>(this->_Value)));
		}

		inline T operator--(Elysium::Core::Template::System::int32_t) noexcept
		{
			T Result = static_cast<T>(_InterlockedDecrement(&reinterpret_cast<volatile long&>(this->_Value)));
			++Result;
			return static_cast<T>(Result);
		}

		// @ToDo
	};

	template <class T>
	class _AtomicIntegral<T, 8>
		: public _AtomicBase<T, 8>
	{
	public:
		constexpr _AtomicIntegral() noexcept = default;

		inline constexpr _AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
			: _AtomicBase<T, 8>(Value)
		{ }

		constexpr _AtomicIntegral(const _AtomicIntegral& Source) = delete;

		constexpr _AtomicIntegral(_AtomicIntegral&& Right) noexcept = delete;

		constexpr ~_AtomicIntegral() = default;
	public:
		inline T operator++() noexcept
		{
			return static_cast<T>(_InterlockedIncrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
		}

		inline T operator++(Elysium::Core::Template::System::int32_t) noexcept
		{
			T Result = static_cast<T>(_InterlockedIncrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
			--Result;
			return static_cast<T>(Result);
		}

		inline T operator--() noexcept
		{
			return static_cast<T>(_InterlockedDecrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
		}

		inline T operator--(Elysium::Core::Template::System::int32_t) noexcept
		{
			T Result = static_cast<T>(_InterlockedDecrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
			++Result;
			return static_cast<T>(Result);
		}

		// @ToDo
	};
}
#endif
#endif
