/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3DOUBLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR3DOUBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3TEMPLATE
#include "Vector3Template.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3SINGLE
#include "Vector3Single.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Numerics
			{
				class ELYSIUM_CORE_MATH_API Vector3Double : public Vector3Template<double>
				{
				public:
					// constructors & destructor
					Vector3Double();
					Vector3Double(double Value);
					Vector3Double(double ValueX, double ValueY, double ValueZ);
					~Vector3Double();

					// static constructors
					static Vector3Double Backward();
					static Vector3Double Down();
					static Vector3Double Forward();
					static Vector3Double Left();
					static Vector3Double One();
					static Vector3Double Right();
					static Vector3Double UnitX();
					static Vector3Double UnitY();
					static Vector3Double UnitZ();
					static Vector3Double Up();
					static Vector3Double Zero();

					// methods
					Vector3Single ToVector3Single();
				};
			}
		}
	}
}
#endif
