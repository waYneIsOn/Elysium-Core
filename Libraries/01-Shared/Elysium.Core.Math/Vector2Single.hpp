/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2SINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR2SINGLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2TEMPLATE
#include "Vector2Template.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Numerics
			{
				class ELYSIUM_CORE_MATH_API Vector2Single : public Vector2Template<float>
				{
				public:
					// constructors & destructor
					Vector2Single();
					Vector2Single(float Value);
					Vector2Single(float ValueX, float ValueY);
					~Vector2Single();

					// static constructors
					static Vector2Single One();
					static Vector2Single UnitX();
					static Vector2Single UnitY();
					static Vector2Single Zero();
				};
			}
		}
	}
}
#endif
