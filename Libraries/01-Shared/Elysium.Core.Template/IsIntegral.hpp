/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGRAL
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGRAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "IsAnyOf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_REMOVECONSTVOLATILE
#include "RemoveConstVolatile.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsIntegralValue = IsAnyOfValue<RemoveConstVolatile<T>::Type, bool, char, signed char, unsigned char, wchar_t, char8_t, char16_t, 
        char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;

    template <class T>
    struct IsIntegral : IntegralConstant<bool, IsIntegralValue<T>>
    { };
}
#endif
