/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL
#define ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGRAL
#include "Integral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#include "_AtomicBase.hpp"
#endif
/*
#define __INTRIN0_INL_H_
#include <intrin0.inl.h>
#endif
*/
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

		constexpr _AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept;

		constexpr _AtomicIntegral(const _AtomicIntegral& Source) = delete;

		constexpr _AtomicIntegral(_AtomicIntegral&& Right) noexcept = delete;

		constexpr ~_AtomicIntegral() = default;
	public:
		T operator++() noexcept;

		T operator++(Elysium::Core::Template::System::int32_t) noexcept;

		T operator--() noexcept;

		T operator--(Elysium::Core::Template::System::int32_t) noexcept;

		// @ToDo
	};

	template<class T>
	inline constexpr _AtomicIntegral<T, 1>::_AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
		: _AtomicBase<T, 1>(Value)
	{ }

	template<class T>
	inline T _AtomicIntegral<T, 1>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), 1));
	}

	template<class T>
	inline T _AtomicIntegral<T, 1>::operator++(Elysium::Core::Template::System::int32_t) noexcept
	{
		T Result = static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), 1));
		--Result;
		return static_cast<T>(Result);
	}

	template<class T>
	inline T _AtomicIntegral<T, 1>::operator--() noexcept
	{
		return static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), -1));
	}

	template<class T>
	inline T _AtomicIntegral<T, 1>::operator--(Elysium::Core::Template::System::int32_t) noexcept
	{
		T Result = static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), -1));
		++Result;
		return static_cast<T>(Result);
	}

	template <class T>
	class _AtomicIntegral<T, 2>
		: public _AtomicBase<T, 2>
	{
	public:
		constexpr _AtomicIntegral() noexcept = default;

		constexpr _AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept;

		constexpr _AtomicIntegral(const _AtomicIntegral& Source) = delete;

		constexpr _AtomicIntegral(_AtomicIntegral&& Right) noexcept = delete;

		constexpr ~_AtomicIntegral() = default;
	public:
		T operator++() noexcept;

		T operator++(Elysium::Core::Template::System::int32_t) noexcept;

		T operator--() noexcept;

		T operator--(Elysium::Core::Template::System::int32_t) noexcept;

		// @ToDo
	};

	template<class T>
	inline constexpr _AtomicIntegral<T, 2>::_AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
		: _AtomicBase<T, 2>(Value)
	{ }

	template<class T>
	inline T _AtomicIntegral<T, 2>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedIncrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
	}

	template<class T>
	inline T _AtomicIntegral<T, 2>::operator++(Elysium::Core::Template::System::int32_t) noexcept
	{
		T Result = static_cast<T>(_InterlockedIncrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
		--Result;
		return static_cast<T>(Result);
	}

	template<class T>
	inline T _AtomicIntegral<T, 2>::operator--() noexcept
	{
		return static_cast<T>(_InterlockedDecrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
	}

	template<class T>
	inline T _AtomicIntegral<T, 2>::operator--(Elysium::Core::Template::System::int32_t) noexcept
	{
		T Result = static_cast<T>(_InterlockedDecrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
		++Result;
		return static_cast<T>(Result);
	}

	template <class T>
	class _AtomicIntegral<T, 4>
		: public _AtomicBase<T, 4>
	{
	public:
		constexpr _AtomicIntegral() noexcept = default;

		constexpr _AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept;

		constexpr _AtomicIntegral(const _AtomicIntegral& Source) = delete;

		constexpr _AtomicIntegral(_AtomicIntegral&& Right) noexcept = delete;

		constexpr ~_AtomicIntegral() = default;
	public:
		T operator++() noexcept;

		T operator++(Elysium::Core::Template::System::int32_t) noexcept;

		T operator--() noexcept;

		T operator--(Elysium::Core::Template::System::int32_t) noexcept;

		// @ToDo
	};

	template<class T>
	inline constexpr _AtomicIntegral<T, 4>::_AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
		: _AtomicBase<T, 4>(Value)
	{ }

	template<class T>
	inline T _AtomicIntegral<T, 4>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedIncrement(&reinterpret_cast<volatile long&>(this->_Value)));
	}

	template<class T>
	inline T _AtomicIntegral<T, 4>::operator++(Elysium::Core::Template::System::int32_t) noexcept
	{
		T Result = static_cast<T>(_InterlockedIncrement(&reinterpret_cast<volatile long&>(this->_Value)));
		--Result;
		return static_cast<T>(Result);
	}

	template<class T>
	inline T _AtomicIntegral<T, 4>::operator--() noexcept
	{
		return static_cast<T>(_InterlockedDecrement(&reinterpret_cast<volatile long&>(this->_Value)));
	}

	template<class T>
	inline T _AtomicIntegral<T, 4>::operator--(Elysium::Core::Template::System::int32_t) noexcept
	{
		T Result = static_cast<T>(_InterlockedDecrement(&reinterpret_cast<volatile long&>(this->_Value)));
		++Result;
		return static_cast<T>(Result);
	}

	template <class T>
	class _AtomicIntegral<T, 8>
		: public _AtomicBase<T, 8>
	{
	public:
		constexpr _AtomicIntegral() noexcept = default;

		constexpr _AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept;

		constexpr _AtomicIntegral(const _AtomicIntegral& Source) = delete;

		constexpr _AtomicIntegral(_AtomicIntegral&& Right) noexcept = delete;

		constexpr ~_AtomicIntegral() = default;
	public:
		T operator++() noexcept;

		T operator++(Elysium::Core::Template::System::int32_t) noexcept;

		T operator--() noexcept;

		T operator--(Elysium::Core::Template::System::int32_t) noexcept;

		// @ToDo
	};

	template<class T>
	inline constexpr _AtomicIntegral<T, 8>::_AtomicIntegral(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
		: _AtomicBase<T, 8>(Value)
	{ }

	template<class T>
	inline T _AtomicIntegral<T, 8>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedIncrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
	}

	template<class T>
	inline T _AtomicIntegral<T, 8>::operator++(Elysium::Core::Template::System::int32_t) noexcept
	{
		T Result = static_cast<T>(_InterlockedIncrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
		--Result;
		return static_cast<T>(Result);
	}

	template<class T>
	inline T _AtomicIntegral<T, 8>::operator--() noexcept
	{
		return static_cast<T>(_InterlockedDecrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
	}

	template<class T>
	inline T _AtomicIntegral<T, 8>::operator--(Elysium::Core::Template::System::int32_t) noexcept
	{
		T Result = static_cast<T>(_InterlockedDecrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
		++Result;
		return static_cast<T>(Result);
	}
}
#endif
