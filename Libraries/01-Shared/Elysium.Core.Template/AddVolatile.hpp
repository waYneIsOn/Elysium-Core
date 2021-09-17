/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_VOLATILE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_VOLATILE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOLATILE
#include "IsVolatile.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    struct AddVolatile
    {
        using Type = Conditional<IsVolatile<T>::Value, T, volatile T>::Type;
    };

    template <class T>
    using AddVolatileType = typename AddVolatile<T>::Type;
}
#endif
