/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLESINGLE
#define ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLESINGLE

#ifndef ELYSIUM_CORE_EXPORT
#include "../../../Libraries/01-Shared/Elysium.Core/Export.hpp"
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
				class EXPORT RectangleSingle : public RectangleTemplate<float>
				{
				public:
					RectangleSingle();
					RectangleSingle(float X, float Y, float Width, float Height);
					~RectangleSingle();
				};
			}
		}
	}
}
#endif
