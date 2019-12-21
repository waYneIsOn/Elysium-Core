/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLESINGLE
#define ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLESINGLE

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLETEMPLATE
#include "RectangleTemplate.hpp"
#endif

namespace Elysium::Core::Math::Geometry
{
	class ELYSIUM_CORE_MATH_API RectangleSingle : public RectangleTemplate<float>
	{
	public:
		RectangleSingle();
		RectangleSingle(float X, float Y, float Width, float Height);
		~RectangleSingle();
	};
}
#endif
