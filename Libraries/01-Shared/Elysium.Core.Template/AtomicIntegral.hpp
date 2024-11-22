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
#include "AtomicBase.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	template <class T, Elysium::Core::Template::System::size SizeOfT = sizeof(T)>
	class AtomicIntegral;

	template <class T>
	class AtomicIntegral<T, 1>
		: public AtomicBase<T, 1>
	{
	public:
		constexpr AtomicIntegral() noexcept = default;

		AtomicIntegral(const AtomicIntegral& Source) = delete;

		AtomicIntegral(AtomicIntegral&& Right) noexcept = delete;

		~AtomicIntegral() = default;
	public:
		T operator++() noexcept;

		// @ToDo
	};

	template<class T>
	inline T AtomicIntegral<T, 1>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedExchangeAdd8(&reinterpret_cast<volatile Elysium::Core::Template::System::int8_t&>(this->_Value), 1));
	}

	template <class T>
	class AtomicIntegral<T, 2>
		: public AtomicBase<T, 2>
	{
	public:
		constexpr AtomicIntegral() noexcept = default;

		AtomicIntegral(const AtomicIntegral& Source) = delete;

		AtomicIntegral(AtomicIntegral&& Right) noexcept = delete;

		~AtomicIntegral() = default;
	public:
		T operator++() noexcept;

		// @ToDo
	};

	template<class T>
	inline T AtomicIntegral<T, 2>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedIncrement16(&reinterpret_cast<volatile Elysium::Core::Template::System::int16_t&>(this->_Value)));
	}

	template <class T>
	class AtomicIntegral<T, 4>
		: public AtomicBase<T, 4>
	{
	public:
		constexpr AtomicIntegral() noexcept = default;

		AtomicIntegral(const AtomicIntegral& Source) = delete;

		AtomicIntegral(AtomicIntegral&& Right) noexcept = delete;

		~AtomicIntegral() = default;
	public:
		T operator++() noexcept;

		// @ToDo
	};

	template<class T>
	inline T AtomicIntegral<T, 4>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedIncrement(&reinterpret_cast<volatile long&>(this->_Value)));
	}

	template <class T>
	class AtomicIntegral<T, 8>
		: public AtomicBase<T, 8>
	{
	public:
		constexpr AtomicIntegral() noexcept = default;

		AtomicIntegral(const AtomicIntegral& Source) = delete;

		AtomicIntegral(AtomicIntegral&& Right) noexcept = delete;

		~AtomicIntegral() = default;
	public:
		T operator++() noexcept;

		// @ToDo
	};

	template<class T>
	inline T AtomicIntegral<T, 8>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedIncrement64(&reinterpret_cast<volatile Elysium::Core::Template::System::int64_t&>(this->_Value)));
	}
}
#endif
