/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLEDOUBLE
#define ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLEDOUBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLETEMPLATE
#include "RectangleTemplate.hpp"
#endif

namespace Elysium::Core::Math::Geometry
{
	class ELYSIUM_CORE_MATH_API RectangleDouble : public RectangleTemplate<double>
	{
	public:
		RectangleDouble();
		RectangleDouble(double X, double Y, double Width, double Height);
		~RectangleDouble();
	};
}
#endif
