/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC
#define ELYSIUM_CORE_TEMPLATE_THREADING_ATOMIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ATOMICUSABLE
#include "../Concepts/AtomicUsable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICENUM
#include "_AtomicEnum.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL
#include "_AtomicIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER
#include "_AtomicPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISBOOLEAN
#include "../TypeTraits/IsBoolean.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISENUMERATION
#include "../TypeTraits/IsEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNOTHROWDEFAULTCONSTRUCTIBLE
#include "../TypeTraits/IsNothrowDefaultConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISPOINTER
#include "../TypeTraits/IsPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_SELECT
#include "../TypeTraits/Select.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	template<class T>
	using SelectAtomicBase = typename TypeTraits::Select<TypeTraits::IsPointerValue<T>>::template
	Apply
	<
		_AtomicPointer<T>,
		typename TypeTraits::Select<TypeTraits::IsBooleanValue<T>>::template
		Apply
		<
			_AtomicBase<T, sizeof(T)>,
			typename TypeTraits::Select<TypeTraits::IsEnumerationValue<T>>::template
			Apply
			<
				_AtomicEnum<T>,
				_AtomicIntegral<T>
			>
		>
	>;
	
	template <class T>
	class Atomic
		: public SelectAtomicBase<T>
	{
	private:
		using Base = SelectAtomicBase<T>;
	public:
		inline constexpr Atomic() noexcept(Elysium::Core::Template::TypeTraits::IsNoThrowDefaultConstructibleValue<T>)
			: Base()
		{ }

		inline constexpr Atomic(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
			: Base(Value)
		{ }

		constexpr Atomic(const Atomic& Source) = delete;

		constexpr Atomic(Atomic&& Right) noexcept = delete;

		constexpr ~Atomic() = default;
	public:
		constexpr Atomic& operator=(const Atomic& Source) = delete;

		constexpr Atomic& operator=(Atomic&& Right) noexcept = delete;
	public:
		inline operator T() const volatile noexcept
		{
			return Load();
		}

		inline operator T() const noexcept
		{
			return Load();
		}
	public:
		inline T operator=(const T Value) volatile noexcept
		{
			Store(Value);
			return Value;
		}

		inline T operator=(const T Value) noexcept
		{
			Store(Value);
			return Value;
		}
	public:
		inline T Load(const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) const volatile noexcept
		{
			return const_cast<const Atomic<T>*>(this)->Base::Load(Order);
		}

		inline void Store(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) volatile noexcept
		{
			const_cast<Atomic<T>*>(this)->Base::Store(Value, Order);
		}

		inline T Exchange(const T Value, const Elysium::Core::Template::Memory::MemoryOrder Order = Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) noexcept
		{
			return const_cast<Atomic<T>*>(this)->Base::Exchange(Value, Order);
		}

		inline bool CompareExchangeStrong(T& Expected, const T Desired, const Elysium::Core::Template::Memory::MemoryOrder Order = 
			Elysium::Core::Template::Memory::MemoryOrder::SequentiallyConsistent) noexcept
		{
			return const_cast<Atomic<T>*>(this)->Base::CompareExchangeStrong(Expected, Desired, Order);
		}

		inline bool CompareExchangeStrong(T& Expected, const T Desired, const Elysium::Core::Template::Memory::MemoryOrder Success,
			const Elysium::Core::Template::Memory::MemoryOrder Failure) noexcept
		{
			return const_cast<Atomic<T>*>(this)->Base::CompareExchangeStrong(Expected, Desired, Success, Failure);
		}
	};
}
#endif
