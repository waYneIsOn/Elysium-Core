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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsIntegerValue = IsAnyOfValue<Functional::RemoveConstVolatileType<T>, 
        Elysium::Core::Template::System::int8_t, Elysium::Core::Template::System::uint8_t, signed char,
        Elysium::Core::Template::System::int16_t, Elysium::Core::Template::System::uint16_t, signed short,
        Elysium::Core::Template::System::int32_t, Elysium::Core::Template::System::uint32_t, signed int, 
        long, unsigned long, signed long,
        Elysium::Core::Template::System::int64_t, Elysium::Core::Template::System::uint64_t, signed long long,
        Elysium::Core::Template::System::size>;

    template <class T>
    struct IsInteger : IntegralConstant<bool, IsIntegerValue<T>>
    { };
}
#endif
