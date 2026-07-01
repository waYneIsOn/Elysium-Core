/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MIN
#define ELYSIUM_CORE_TEMPLATE_MATH_MIN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASOPERATORLESSOREQUAL
#include "../Concepts/HasOperatorLessOrEqual.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CALLTRAITS
#include "../TypeTraits/CallTraits.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	template <Elysium::Core::Template::Concepts::HasOperatorLessOrEqual T>
	inline constexpr typename Elysium::Core::Template::TypeTraits::CallTraits<T>::ValueType _MinImplementation(typename Elysium::Core::Template::TypeTraits::CallTraits<T>::ParameterType Left,
		typename Elysium::Core::Template::TypeTraits::CallTraits<T>::ParameterType Right) noexcept(noexcept(Left <= Right))
	{
		return Left <= Right ? Left : Right;
	}

	template <Elysium::Core::Template::Concepts::HasOperatorLessOrEqual T>
	inline constexpr typename Elysium::Core::Template::TypeTraits::CallTraits<T>::ValueType Min(T Left, T Right) noexcept(noexcept(Left <= Right))
	{
		return _MinImplementation<T>(Left, Right);
	}
}
#endif
