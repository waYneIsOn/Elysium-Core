/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNSIGNEDINTEGER
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNSIGNEDINTEGER

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
    inline constexpr bool IsUnsignedIntegerValue = IsAnyOfValue<Functional::RemoveConstVolatileType<T>, unsigned char, unsigned short, unsigned int,
        unsigned long, unsigned long long>;

    template <class T>
    struct IsUnsignedInteger : IntegralConstant<bool, IsUnsignedIntegerValue<T>>
    { };
}
#endif
