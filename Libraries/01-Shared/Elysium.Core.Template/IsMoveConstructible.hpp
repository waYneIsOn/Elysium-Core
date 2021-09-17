/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVECONSTRUCTIBLE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVECONSTRUCTIBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    struct IsMoveConstructible : IntegralConstant<bool, __is_constructible(T, T)>
    { };

    template <class T>
    inline constexpr bool IsMoveConstructibleValue = __is_constructible(T, T);
}
#endif
