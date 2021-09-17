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

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "IsSame.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
    template <class T>
    class Array;
}

namespace Elysium::Core::Template::TypeTraits
{
    template <class>
    inline constexpr bool IsArrayValue = false;
    
    template <class T>
    inline constexpr bool IsArrayValue<T[]> = true;

    template <class T, size_t Size>
    inline constexpr bool IsArrayValue<T[Size]> = true;

    template <template<class> class T, class Inner>
    inline constexpr bool IsArrayValue<T<Inner>> = IsSame<RemoveConstVolatile<T<Inner>>::Type, Elysium::Core::Collections::Template::Array<Inner>>();

    template <class T>
    struct IsArray : IntegralConstant<bool, IsArrayValue<T>>
    { };
}
#endif
