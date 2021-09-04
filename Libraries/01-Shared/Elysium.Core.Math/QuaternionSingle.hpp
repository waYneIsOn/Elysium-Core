/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONSINGLE
#define ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONSINGLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNION
#include "Quaternion.hpp"
#endif

template class ELYSIUM_CORE_MATH_API Elysium::Core::Math::Numerics::Quaternion<float>;
#endif
