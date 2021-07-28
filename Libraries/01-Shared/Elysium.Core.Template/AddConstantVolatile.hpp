/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ADDCONSTANTVOLATILE
#define ELYSIUM_CORE_TEMPLATE_ADDCONSTANTVOLATILE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONDITIONAL
#include "Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISCONSTANT
#include "IsConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISVOLATILE
#include "IsVolatile.hpp"
#endif

namespace Elysium::Core::Template
{
    template <class T>
    struct AddConstantVolatile
    {
        using Type = Conditional<IsConstant<T>::Value,
            Conditional<IsVolatile<T>::Value, T, volatile T>,
            Conditional<IsVolatile<T>::Value, const T, const volatile T>
        >::Type;
    };

    template <class T>
    using AddConstantVolatileType = typename AddConstantVolatile<T>::Type;
}
#endif
