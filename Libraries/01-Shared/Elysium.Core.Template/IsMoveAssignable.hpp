/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVEASSIGNABLE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVEASSIGNABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_ADDLEFTVALUEREFERENCE
#include "AddLeftValueReference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsMoveAssignableValue = __is_assignable(Functional::AddLeftValueReferenceType<T>, T);

    template <class T>
    struct IsMoveAssignable : IntegralConstant<bool, __is_assignable(Functional::AddLeftValueReferenceType<T>, T)>
    { };
}
#endif
