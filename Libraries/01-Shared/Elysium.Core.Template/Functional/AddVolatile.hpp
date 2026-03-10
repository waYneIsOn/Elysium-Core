/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_ADDVOLATILE
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_ADDVOLATILE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOLATILE
#include "IsVolatile.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
    template <class T>
    struct AddVolatile
    {
        using Type = Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsVolatile<T>::Value, T, volatile T>;
    };

    template <class T>
    using AddVolatileType = typename AddVolatile<T>::Type;
}
#endif
