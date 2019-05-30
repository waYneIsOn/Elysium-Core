#pragma once
/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4DOUBLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR4DOUBLE

#ifndef ELYSIUM_CORE_EXPORT
#include "../../../Libraries/01-Shared/Elysium.Core/Export.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4TEMPLATE
#include "Vector4Template.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4SINGLE
#include "Vector4Single.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Numerics
			{
				class EXPORT Vector4Double : public Vector4Template<double>
				{
				public:
					// constructors & destructor
					Vector4Double();
					Vector4Double(double Value);
					Vector4Double(double ValueX, double ValueY, double ValueZ, double ValueW);
					~Vector4Double();

					// static constructors
					static Vector4Double One();
					static Vector4Double UnitX();
					static Vector4Double UnitY();
					static Vector4Double UnitZ();
					static Vector4Double UnitW();
					static Vector4Double Zero();

					// methods
					Vector4Single ToVector4Single();
				};
			}
		}
	}
}
#endif
