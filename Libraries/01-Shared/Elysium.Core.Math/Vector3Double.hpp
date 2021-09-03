/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3DOUBLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR3DOUBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3TEMPLATE
#include "Vector3Template.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3SINGLE
#include "Vector3Single.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
#define Vector3Double Vector3Template<double>
}
#endif
