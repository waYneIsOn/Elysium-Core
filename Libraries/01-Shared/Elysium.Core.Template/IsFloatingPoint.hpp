/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ISFLOATINGPOINT
#define ELYSIUM_CORE_TEMPLATE_ISFLOATINGPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISANYOF
#include "IsAnyOf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

namespace Elysium::Core
{
    class Decimal;
}

namespace Elysium::Core::Template
{
    template <class T>
    inline constexpr bool IsFloatingPointValue = IsAnyOfValue<RemoveConstVolatile<T>::Type, float, double, long double, Elysium::Core::Decimal>;

    template <class T>
    struct IsFloatingPoint : IntegralConstant<bool, IsFloatingPointValue<T>>
    { };
}
#endif
