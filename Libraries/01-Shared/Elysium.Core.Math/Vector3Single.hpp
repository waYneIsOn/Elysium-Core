/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3SINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR3SINGLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3TEMPLATE
#include "Vector3Template.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
#define Vector3Single Vector3Template<float>
}
#endif
