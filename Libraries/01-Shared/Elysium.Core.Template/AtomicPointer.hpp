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

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#include "AtomicBase.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	template <class T>
	class AtomicPointer
		: public AtomicBase<T, sizeof(void*)>
	{
	public:
		constexpr AtomicPointer() noexcept = default;

		AtomicPointer(const AtomicPointer& Source) = delete;

		AtomicPointer(AtomicPointer&& Right) noexcept = delete;

		~AtomicPointer() = default;
	};
}
#endif
