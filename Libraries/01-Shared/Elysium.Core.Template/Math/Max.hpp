/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_MAX
#define ELYSIUM_CORE_TEMPLATE_MATH_MAX

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASOPERATORGREATEROREQUAL
#include "../Concepts/HasOperatorGreaterOrEqual.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CALLTRAITS
#include "../TypeTraits/CallTraits.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	template <Elysium::Core::Template::Concepts::HasOperatorGreaterOrEqual T>
	inline constexpr typename Elysium::Core::Template::TypeTraits::CallTraits<T>::ValueType _MaxImplementation(typename Elysium::Core::Template::TypeTraits::CallTraits<T>::ParameterType Left,
		typename Elysium::Core::Template::TypeTraits::CallTraits<T>::ParameterType Right) noexcept(noexcept(Left >= Right))
	{
		return Left >= Right ? Left : Right;
	}

	template <Elysium::Core::Template::Concepts::HasOperatorGreaterOrEqual T>
	inline constexpr typename Elysium::Core::Template::TypeTraits::CallTraits<T>::ValueType Max(T Left, T Right) noexcept(noexcept(Left >= Right))
	{
		return _MaxImplementation<T>(Left, Right);
	}
}
#endif
