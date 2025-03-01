/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISARRAY
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISARRAY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "IsSame.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class>
    inline constexpr bool IsArrayValue = false;
    
    template <class T>
    inline constexpr bool IsArrayValue<T[]> = true;

    template <class T, Elysium::Core::Template::System::size Size>
    inline constexpr bool IsArrayValue<T[Size]> = true;
    
    template <class T>
    struct IsArray : IntegralConstant<bool, IsArrayValue<T>>
    { };
}
#endif
