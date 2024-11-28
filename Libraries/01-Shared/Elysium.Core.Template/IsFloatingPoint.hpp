/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLOATINGPOINT
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLOATINGPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "IsAnyOf.hpp"
#endif

namespace Elysium::Core::Template::Math
{
    class Decimal;
}

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsFloatingPointValue = IsAnyOfValue<Functional::RemoveConstVolatile<T>::Type, float, double, long double, 
        Elysium::Core::Template::Math::Decimal>;

    template <class T>
    struct IsFloatingPoint : IntegralConstant<bool, IsFloatingPointValue<T>>
    { };
}
#endif
