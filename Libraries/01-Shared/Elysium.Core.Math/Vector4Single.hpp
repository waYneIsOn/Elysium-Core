/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4SINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR4SINGLE

#ifndef ELYSIUM_CORE_EXPORT
#include "../../../Libraries/01-Shared/Elysium.Core/Export.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4TEMPLATE
#include "Vector4Template.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Numerics
			{
				class EXPORT Vector4Single : public Vector4Template<float>
				{
				public:
					// constructors & destructor
					Vector4Single();
					Vector4Single(float Value);
					Vector4Single(float ValueX, float ValueY, float ValueZ, float ValueW);
					~Vector4Single();

					// static constructors
					static Vector4Single One();
					static Vector4Single UnitX();
					static Vector4Single UnitY();
					static Vector4Single UnitZ();
					static Vector4Single UnitW();
					static Vector4Single Zero();
				};
			}
		}
	}
}
#endif
