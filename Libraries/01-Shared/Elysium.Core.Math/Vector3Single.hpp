/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3SINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR3SINGLE

#ifndef ELYSIUM_CORE_EXPORT
#include "../../../Libraries/01-Shared/Elysium.Core/Export.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3TEMPLATE
#include "Vector3Template.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Numerics
			{
				class EXPORT Vector3Single : public Vector3Template<float>
				{
				public:
					// constructors & destructor
					Vector3Single();
					Vector3Single(float Value);
					Vector3Single(float ValueX, float ValueY, float ValueZ);
					~Vector3Single();

					// static constructors
					static Vector3Single Backward();
					static Vector3Single Down();
					static Vector3Single Forward();
					static Vector3Single Left();
					static Vector3Single One();
					static Vector3Single Right();
					static Vector3Single UnitX();
					static Vector3Single UnitY();
					static Vector3Single UnitZ();
					static Vector3Single Up();
					static Vector3Single Zero();
				};
			}
		}
	}
}
#endif
