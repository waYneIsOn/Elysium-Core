/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISCLASS
#define ELYSIUM_CORE_TEMPLATE_ISCLASS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
{
    /*
    template <class>
    inline constexpr bool IsClassValue = false;

    template <class T>
    inline constexpr bool IsClassValue = true;
    */
    /*
    template <class T>
    struct IsClass : IntegralConstant<bool, IsFloatingPointValue<T>>
    { };
    */
}
#endif
