/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICENUM
#define ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICENUM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_ATOMICBASE
#include "../_AtomicBase.hpp"
#endif

namespace Elysium::Core::Template::Threading
{
	/// <summary>
	/// 
	/// </summary>
	template <class T>
	class _AtomicEnum
		: public _AtomicBase<T, sizeof(T)>
	{
	public:
		constexpr _AtomicEnum() noexcept = default;

		constexpr _AtomicEnum(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept;

		constexpr _AtomicEnum(const _AtomicEnum& Source) = delete;

		constexpr _AtomicEnum(_AtomicEnum&& Right) noexcept = delete;

		constexpr ~_AtomicEnum() = default;
	};

	template<class T>
	inline constexpr _AtomicEnum<T>::_AtomicEnum(Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsReferenceValue<T>, T, const T> Value) noexcept 
		: _AtomicBase<T, sizeof(T)>(Value)
	{ }
}
#endif
