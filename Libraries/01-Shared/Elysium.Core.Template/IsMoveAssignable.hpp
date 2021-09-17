/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISMOVEASSIGNABLE
#define ELYSIUM_CORE_TEMPLATE_ISMOVEASSIGNABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ADDLEFTVALUEREFERENCE
#include "AddLeftValueReference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
{
    template <class T>
    struct IsMoveAssignable : IntegralConstant<bool, __is_assignable(AddLeftValueReferenceType<T>, T)>
    { };
    
    template <class T>
    inline constexpr bool IsMoveAssignableValue = __is_assignable(AddLeftValueReferenceType<T>, T);
}
#endif
