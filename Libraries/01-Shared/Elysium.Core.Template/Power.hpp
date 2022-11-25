/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_POWER
#define ELYSIUM_CORE_TEMPLATE_MATH_POWER

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Math
{
	constexpr double Power(const double Base, const double Exponent) noexcept
	{
		// ToDo: this can be done way better!
		double Result = 1;
		for (double i = 0; i < Exponent; i++)
		{
			Result *= Base;
		}

		return Result;
	}
}
#endif
