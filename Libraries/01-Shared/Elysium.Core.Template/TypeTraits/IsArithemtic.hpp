/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISARITHMETIC
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISARITHMETIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLOATINGPOINT
#include "IsFloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGRAL
#include "IsIntegral.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsArithmeticValue = IsFloatingPointValue<T> || IsIntegralValue<T>;

    template <class T>
    struct IsArithmetic : IntegralConstant<bool, IsArithmeticValue<T>>
    { };
}
#endif
