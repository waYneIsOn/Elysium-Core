/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONDOUBLE
#define ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONDOUBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONTEMPLATE
#include "QuaternionTemplate.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	class ELYSIUM_CORE_MATH_API QuaternionDouble : public QuaternionTemplate<double>
	{
	public:
		// constructors & destructor
		QuaternionDouble(double ValueX, double ValueY, double ValueZ, double ValueW);
		~QuaternionDouble();

		// static constructors
		static QuaternionDouble Identity();
	};
}
#endif
