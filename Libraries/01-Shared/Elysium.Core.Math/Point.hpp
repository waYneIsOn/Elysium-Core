/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_GEOMETRY_POINT
#define ELYSIUM_CORE_MATH_GEOMETRY_POINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Math::Geometry
{
	class ELYSIUM_CORE_MATH_API Point final
	{
	public:
		Point();
		Point(Elysium::Core::uint32_t X, Elysium::Core::uint32_t Y);
		Point(const Point& Source);
		Point(Point&& Right) noexcept;
		~Point();

		Point& operator=(const Point& Source);
		Point& operator=(Point&& Right) noexcept;

		Elysium::Core::int32_t X;
		Elysium::Core::int32_t Y;
	};
}
#endif
