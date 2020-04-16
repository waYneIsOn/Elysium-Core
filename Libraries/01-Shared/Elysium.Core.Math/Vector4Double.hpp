/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4DOUBLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR4DOUBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4TEMPLATE
#include "Vector4Template.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4SINGLE
#include "Vector4Single.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	class ELYSIUM_CORE_MATH_API Vector4Double : public Vector4Template<double>
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
#endif
