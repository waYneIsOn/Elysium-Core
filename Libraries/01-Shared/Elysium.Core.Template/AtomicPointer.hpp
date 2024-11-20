/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER
#define ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#include "AtomicBase.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	template <Elysium::Core::Template::Concepts::Pointer T>
	class AtomicPointer
		: public AtomicBase<T, sizeof(void*)>
	{
	public:
		constexpr AtomicPointer() noexcept = default;

		AtomicPointer(const AtomicPointer& Source) = delete;

		AtomicPointer(AtomicPointer&& Right) noexcept = delete;

		~AtomicPointer() = default;
	public:
		T operator++() noexcept;

		// @ToDo
	};

	template<Elysium::Core::Template::Concepts::Pointer T>
	inline T AtomicPointer<T>::operator++() noexcept
	{
#if ELYSIUM_CORE_BITNESS == 64
		Elysium::Core::Template::System::int64_t Result = 
			_InterlockedExchangeAdd64(reinterpret_cast<volatile Elysium::Core::Template::System::int64_t*>(this->_Value), 1);
#elif ELYSIUM_CORE_BITNESS == 32
		long Result = 
			_InterlockedExchangeAdd(reinterpret_cast<volatile long*>(this->_Value), 1);
#else
#error "unsupported os regarding bitness"
#endif

		return reinterpret_cast<T>(Result);
	}
}
#endif
