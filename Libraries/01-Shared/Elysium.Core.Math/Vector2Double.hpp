/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2DOUBLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR2DOUBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2TEMPLATE
#include "Vector2Template.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2SINGLE
#include "Vector2Single.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Numerics
			{
				class ELYSIUM_CORE_MATH_API Vector2Double : public Vector2Template<double>
				{
				public:
					// constructors & destructor
					Vector2Double();
					Vector2Double(double Value);
					Vector2Double(double ValueX, double ValueY);
					~Vector2Double();

					// static constructors
					static Vector2Double One();
					static Vector2Double UnitX();
					static Vector2Double UnitY();
					static Vector2Double Zero();

					// methods
					Vector2Single ToVector2Single();
				};
			}
		}
	}
}
#endif
