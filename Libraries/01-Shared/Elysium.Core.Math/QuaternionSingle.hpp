/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONSINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONSINGLE

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONTEMPLATE
#include "QuaternionTemplate.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	class ELYSIUM_CORE_MATH_API QuaternionSingle : public QuaternionTemplate<float>
	{
	public:
		// constructors & destructor
		QuaternionSingle(float ValueX, float ValueY, float ValueZ, float ValueW);
		~QuaternionSingle();

		// static constructors
		static QuaternionSingle Identity();
	};
}
#endif
