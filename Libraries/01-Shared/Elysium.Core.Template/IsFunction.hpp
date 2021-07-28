/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISFUNCTION
#define ELYSIUM_CORE_TEMPLATE_ISFUNCTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISCONSTANT
#include "IsConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISREFERENCE
#include "IsReference.hpp"
#endif

namespace Elysium::Core::Template
{
    template <class T>
    inline constexpr bool IsFunctionValue = !IsConstantValue<const T> && !IsReferenceValue<T>;

    template <class T>
    struct IsFunction : IntegralConstant<bool, IsFunctionValue<T>>
    { };
}
#endif
