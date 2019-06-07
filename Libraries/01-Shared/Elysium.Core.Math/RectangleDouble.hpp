/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLEDOUBLE
#define ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLEDOUBLE

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLETEMPLATE
#include "RectangleTemplate.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Geometry
			{
				class ELYSIUM_CORE_MATH_API RectangleDouble : public RectangleTemplate<double>
				{
				public:
					RectangleDouble();
					RectangleDouble(double X, double Y, double Width, double Height);
					~RectangleDouble();
				};
			}
		}
	}
}
#endif
