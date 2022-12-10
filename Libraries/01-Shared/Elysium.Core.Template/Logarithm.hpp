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

#ifndef _CMATH_
// ToDo: implement myself and remove
#include <cmath>
#endif

namespace Elysium::Core::Template::Math
{
	inline float Logarithm(float Value) noexcept
	{
		return logf(Value);
	}
	/*
	template <class T, std::enable_if<std::is_integral_v<T>, int> = 0>
	inline T Logarithm(T Value) noexcept
	{
		return log(Value);
	}
	
	template <float, std::enable_if<true, float>>
	inline float Logarithm(float Value) noexcept
	{
		return logf(Value);
	}

	template <double, std::enable_if<true, double>>
	inline double Logarithm(double Value) noexcept
	{
		return log(Value);
	}

	template <long double, std::enable_if<true, long double>>
	inline long double Logarithm(long double Value) noexcept
	{
		return logl(Value);
	}
	*/
}
#endif
