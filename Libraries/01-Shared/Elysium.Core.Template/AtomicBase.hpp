/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#define ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMORYORDER
#include "MemoryOrder.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	template <class T, Elysium::Core::Template::System::size TSize>
	class AtomicBase
	{
	public:
		constexpr AtomicBase() noexcept = default;

		AtomicBase(const AtomicBase& Source) = delete;

		AtomicBase(AtomicBase&& Right) noexcept = delete;

		~AtomicBase() = default;
	public:
		AtomicBase& operator=(const AtomicBase& Source) = delete;

		AtomicBase& operator=(AtomicBase&& Right) noexcept = delete;
	protected:
		T Load(const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) const noexcept;
		
		T Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) noexcept;
	protected:
		T _Value;
	};

	template<class T, Elysium::Core::Template::System::size TSize>
	inline T AtomicBase<T, TSize>::Load(const Elysium::Core::Template::Memory::MemoryOrder Order) const noexcept
	{
		// @ToDo: validate memory order!

		// @ToDo: this cannot work every time! need to somehow force some synchronization here as well!
		T CopiedValue = _Value;

		return CopiedValue;
	}

	template<class T, Elysium::Core::Template::System::size TSize>
	inline T AtomicBase<T, TSize>::Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order) noexcept
	{
		// @ToDo: validate memory order!

		// @ToDo: this cannot work every time! need to somehow force some synchronization here as well!
		T CopiedValue = _Value;
		_Value = Value;

		return CopiedValue;
	}
}
#endif
