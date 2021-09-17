/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ADDCONSTANTVOLATILE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ADDCONSTANTVOLATILE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONSTANT
#include "IsConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOLATILE
#include "IsVolatile.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
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
