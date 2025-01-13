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
#include "AtomicUsable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICINTEGRAL
#include "_AtomicIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICPOINTER
#include "_AtomicPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISBOOLEAN
#include "IsBoolean.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNOTHROWDEFAULTCONSTRUCTIBLE
#include "IsNothrowDefaultConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISPOINTER
#include "IsPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_SELECT
#include "Select.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
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
				_AtomicIntegral<T>
			>
		>;
	
	template <class T>
	class Atomic
		: public SelectAtomicBase<T>
	{
	private:
		using Base = SelectAtomicBase<T>;
	public:
		constexpr Atomic() noexcept(Elysium::Core::Template::TypeTraits::IsNoThrowDefaultConstructibleValue<T>);

		constexpr Atomic(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept;

		Atomic(const Atomic& Source) = delete;

		Atomic(Atomic&& Right) noexcept = delete;

		~Atomic() = default;
	public:
		Atomic& operator=(const Atomic& Source) = delete;

		Atomic& operator=(Atomic&& Right) noexcept = delete;
	public:
		operator T() const volatile noexcept;

		operator T() const noexcept;
	public:
		T operator=(const T Value) volatile noexcept;

		T operator=(const T Value) noexcept;
	public:
		T Load() const volatile noexcept;

		void Store(const T Value) volatile noexcept;
	};

	template<class T>
	inline constexpr Atomic<T>::Atomic() noexcept(Elysium::Core::Template::TypeTraits::IsNoThrowDefaultConstructibleValue<T>)
		: Base()
	{ }

	template<class T>
	inline constexpr Atomic<T>::Atomic(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept
		: Base(Value)
	{ }

	template<class T>
	inline Atomic<T>::operator T() const volatile noexcept
	{
		return Load();
	}

	template<class T>
	inline Atomic<T>::operator T() const noexcept
	{
		return Load();
	}

	template<class T>
	inline T Atomic<T>::operator=(const T Value) volatile noexcept
	{
		Store(Value);
		return Value;
	}

	template<class T>
	inline T Atomic<T>::operator=(const T Value) noexcept
	{
		Store(Value);
		return Value;
	}

	template<class T>
	inline T Atomic<T>::Load() const volatile noexcept
	{
		return const_cast<const Atomic<T>*>(this)->Base::Load();
	}

	template<class T>
	inline void Atomic<T>::Store(const T Value) volatile noexcept
	{
		const_cast<Atomic<T>*>(this)->Base::Store(Value);
	}
}
#endif
