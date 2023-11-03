/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOPYCONSTRUCTIBLE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOPYCONSTRUCTIBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    struct IsCopyConstructible : IntegralConstant<bool, __is_constructible(T, const T&)>
    { };

    template <class T>
    inline constexpr bool IsCopyConstructibleValue = __is_constructible(T, const T&);
}
#endif
