/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISARITHMETIC
#define ELYSIUM_CORE_TEMPLATE_ISARITHMETIC

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISFLOATINGPOINT
#include "IsFloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISINTEGRAL
#include "IsIntegral.hpp"
#endif

namespace Elysium::Core::Template
{
    template <class T>
    inline constexpr bool IsArithmeticValue = IsFloatingPointValue<T> || IsIntegralValue<T>;

    template <class T>
    struct IsArithmetic : IntegralConstant<bool, IsArithmeticValue<T>>
    { };
}
#endif
