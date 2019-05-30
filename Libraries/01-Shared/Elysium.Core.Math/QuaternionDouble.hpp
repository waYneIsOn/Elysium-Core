#pragma once
/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONDOUBLE
#define ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONDOUBLE

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
				class EXPORT QuaternionDouble : public QuaternionTemplate<double>
				{
				public:
					// constructors & destructor
					QuaternionDouble(double ValueX, double ValueY, double ValueZ, double ValueW);
					~QuaternionDouble();

					// static constructors
					static QuaternionDouble Identity();
				};
			}
		}
	}
}
#endif
