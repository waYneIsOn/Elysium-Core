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
	template <Elysium::Core::Template::Concepts::Integral T, Elysium::Core::Template::System::size TSize = sizeof(T)>
	struct AtomicIntegral;

	template <Elysium::Core::Template::Concepts::Integral T>
	struct AtomicIntegral<T, 1>
		: public AtomicBase<T, 1>
	{
		// @ToDo
	};

	template <Elysium::Core::Template::Concepts::Integral T>
	struct AtomicIntegral<T, 2>
		: AtomicBase<T, 2>
	{
		// @ToDo
	};

	template <Elysium::Core::Template::Concepts::Integral T>
	struct AtomicIntegral<T, 4>
		: AtomicBase<T, 4>
	{
		// @ToDo
	public:
		T operator++() noexcept;
	};

	template <Elysium::Core::Template::Concepts::Integral T>
	struct AtomicIntegral<T, 8>
		: AtomicBase<T, 8>
	{
		// @ToDo
	};

	template<Elysium::Core::Template::Concepts::Integral T>
	inline T AtomicIntegral<T, 4>::operator++() noexcept
	{
		return static_cast<T>(_InterlockedIncrement(&reinterpret_cast<volatile long&>(this->_Value)));
	}
}
#endif
