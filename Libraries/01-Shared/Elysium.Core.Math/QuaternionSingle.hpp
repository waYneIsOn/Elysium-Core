/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONSINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONSINGLE

#ifndef ELYSIUM_CORE_EXPORT
#include "../../../Libraries/01-Shared/Elysium.Core/Export.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONTEMPLATE
#include "QuaternionTemplate.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Numerics
			{
				class EXPORT QuaternionSingle : public QuaternionTemplate<float>
				{
				public:
					// constructors & destructor
					QuaternionSingle(float ValueX, float ValueY, float ValueZ, float ValueW);
					~QuaternionSingle();

					// static constructors
					static QuaternionSingle Identity();
				};
			}
		}
	}
}
#endif
