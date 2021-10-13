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
        using Type = Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsConstant<T>::Value,
            Elysium::Core::Template::TypeTraits::Conditional<Elysium::Core::Template::TypeTraits::IsVolatile<T>::Value, T, volatile T>,
            Elysium::Core::Template::TypeTraits::Conditional<Elysium::Core::Template::TypeTraits::IsVolatile<T>::Value, const T, const volatile T>
        >;
    };

    template <class T>
    using AddConstantVolatileType = typename Elysium::Core::Template::TypeTraits::AddConstantVolatile<T>::Type;
}
#endif
