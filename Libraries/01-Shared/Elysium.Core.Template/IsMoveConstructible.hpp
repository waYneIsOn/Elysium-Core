/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISMOVECONSTRUCTIBLE
#define ELYSIUM_CORE_TEMPLATE_ISMOVECONSTRUCTIBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
{
    template <class T>
    struct IsMoveConstructible : IntegralConstant<bool, __is_constructible(T, T)>
    { };

    template <class T>
    inline constexpr bool IsMoveConstructibleValue = __is_constructible(T, T);
}
#endif
