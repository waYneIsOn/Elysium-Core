/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2DOUBLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR2DOUBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2TEMPLATE
#include "Vector2Template.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2SINGLE
#include "Vector2Single.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
#define Vector2Double Vector2Template<double>
}
#endif
