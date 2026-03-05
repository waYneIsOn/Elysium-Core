/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_ROUND
#define ELYSIUM_CORE_TEMPLATE_MATH_ROUND

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef _CMATH_
// ToDo: implement myself and remove
#include <cmath>
#endif

namespace Elysium::Core::Template::Math
{
	template<Concepts::FloatingPoint FP>
	constexpr FP Round(const FP Value) noexcept
	{
		return std::round(Value);
	}
}
#endif
