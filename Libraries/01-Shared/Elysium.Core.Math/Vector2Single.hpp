/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2SINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR2SINGLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2TEMPLATE
#include "Vector2Template.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
#define Vector2Single Vector2Template<float>
}
#endif
