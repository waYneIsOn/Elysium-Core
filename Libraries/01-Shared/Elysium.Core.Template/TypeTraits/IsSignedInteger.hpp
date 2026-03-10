/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNEDINTEGER
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNEDINTEGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "IsAnyOf.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsSignedIntegerValue = IsAnyOfValue<Functional::RemoveConstVolatileType<T>, char, short, int,
        long, long long>;

    template <class T>
    struct IsSignedInteger : IntegralConstant<bool, IsSignedIntegerValue<T>>
    { };
}
#endif
