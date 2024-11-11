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
		/*
		constexpr AtomicBase();

		AtomicBase(const AtomicBase& Source) = delete;

		AtomicBase(AtomicBase&& Right) noexcept = delete;

		~AtomicBase();
		*/
	public:
		AtomicBase& operator=(const AtomicBase& Source) = delete;

		AtomicBase& operator=(AtomicBase&& Right) noexcept = delete;
	public:
		T Load(const Elysium::Core::Template::Memory::MemoryOrder MemoryOrder = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) const noexcept;
		
		void Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder MemoryOrder = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) noexcept;
	private:

	protected:
		T _Value;
	};

	template<class T, Elysium::Core::Template::System::size TSize>
	inline T AtomicBase<T, TSize>::Load(const Elysium::Core::Template::Memory::MemoryOrder MemoryOrder) const noexcept
	{
		// @ToDo: MemoryOrder
		T CopiedValue = _Value;
		return CopiedValue;
	}

	template<class T, Elysium::Core::Template::System::size TSize>
	inline void AtomicBase<T, TSize>::Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder MemoryOrder) noexcept
	{
		// @ToDo: MemoryOrder
		_Value = Value;
	}
}
#endif
