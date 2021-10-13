/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLE
#define ELYSIUM_CORE_MATH_GEOMETRY_RECTANGLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::Math::Geometry
{
	class ELYSIUM_CORE_MATH_API Rectangle final
	{
	public:
		Rectangle();
		Rectangle(Elysium::Core::uint32_t X, Elysium::Core::uint32_t Y, Elysium::Core::uint32_t Width, Elysium::Core::uint32_t Height);
		Rectangle(const Rectangle& Source);
		Rectangle(Rectangle&& Right) noexcept;
		~Rectangle();

		Rectangle& operator=(const Rectangle& Source);
		Rectangle& operator=(Rectangle&& Right) noexcept;

		Elysium::Core::int32_t X;
		Elysium::Core::int32_t Y;
		Elysium::Core::int32_t Width;
		Elysium::Core::int32_t Height;

		const bool Contains(const Rectangle& Other) const;

		void Inflate(const Elysium::Core::uint32_t HorizontalAmount, const Elysium::Core::uint32_t VerticalAmount);

		const bool Intersects(const Rectangle& Other) const;
	};
}
#endif
