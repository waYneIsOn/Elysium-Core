/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2SINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR2SINGLE

#ifndef ELYSIUM_CORE_EXPORT
#include "../../../Libraries/01-Shared/Elysium.Core/Export.hpp"
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
				class EXPORT Vector2Single : public Vector2Template<float>
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
