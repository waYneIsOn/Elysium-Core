/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNICODECHARACTER
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNICODECHARACTER

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
    inline constexpr bool IsUnicodeCharacterValue = IsAnyOfValue<Functional::RemoveConstVolatileType<T>, wchar_t, char8_t, char16_t, char32_t>;

    template <class T>
    struct IsUnicodeCharacter : IntegralConstant<bool, IsUnicodeCharacterValue<T>>
    { };
}
#endif
