/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4SINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR4SINGLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4TEMPLATE
#include "Vector4Template.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	class ELYSIUM_CORE_MATH_API Vector4Single : public Vector4Template<float>
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
#endif
