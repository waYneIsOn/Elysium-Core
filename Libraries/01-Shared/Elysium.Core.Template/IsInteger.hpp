/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGER
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGER

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
    inline constexpr bool IsIntegerValue = IsAnyOfValue<Functional::RemoveConstVolatileType<T>, char, unsigned char, signed char, 
        short, unsigned short, signed short, int, unsigned int, signed int, long, unsigned long, signed long,
        long long, unsigned long long, signed long long>;

    template <class T>
    struct IsInteger : IntegralConstant<bool, IsIntegerValue<T>>
    { };
}
#endif
