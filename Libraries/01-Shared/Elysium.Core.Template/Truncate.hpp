/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_TRUNCATE
#define ELYSIUM_CORE_TEMPLATE_MATH_TRUNCATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLOATINGPOINT
#include "FloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Math
{
	/// <summary>
	/// Calculates the integral part of a floating-point.
	/// </summary>
	/// <param name="Value"></param>
	/// <returns></returns>
	template<Concepts::FloatingPoint FP, Concepts::Integer I>
	constexpr I Truncate(const FP Value) noexcept
	{
		return static_cast<I>(Value);
	}
}
#endif
