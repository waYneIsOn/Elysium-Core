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

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsUnsignedIntegerValue = IsAnyOfValue<Functional::RemoveConstVolatileType<T>, Elysium::Core::Template::System::uint8_t, 
        Elysium::Core::Template::System::uint16_t, Elysium::Core::Template::System::uint32_t, Elysium::Core::Template::System::uint64_t,
        Elysium::Core::Template::System::size>;
    
    template <class T>
    struct IsUnsignedInteger : IntegralConstant<bool, IsUnsignedIntegerValue<T>>
    { };
}
#endif
