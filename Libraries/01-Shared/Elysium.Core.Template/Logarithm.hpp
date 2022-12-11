/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_LOGARITHM
#define ELYSIUM_CORE_TEMPLATE_MATH_LOGARITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLOATINGPOINT
#include "FloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGER
#include "Integer.hpp"
#endif

#ifndef _CMATH_
// ToDo: implement myself and remove
#include <cmath>
#endif

namespace Elysium::Core::Template::Math
{
	template<Concepts::FloatingPoint FP>
	constexpr FP Logarithm(const FP Value) noexcept
	{
		return log(Value);
	}

	template<Concepts::Integer I>
	constexpr double Logarithm(const I Value) noexcept
	{
		return log(Value);
	}
}
#endif
