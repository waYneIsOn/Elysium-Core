/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIAL
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    struct IsTrivial : IntegralConstant<bool, __is_trivial(T)>
    {
    };

    template <class T>
    inline constexpr bool IsTrivialValue = __is_trivial(T);
}
#endif
