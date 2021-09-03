/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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
#define Vector4Double Vector4Template<double>
}
#endif
