/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCHARACTER
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCHARACTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "IsAnyOf.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsCharacterValue = IsAnyOfValue<Functional::RemoveConstVolatile<T>::Type, char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t>;

    template <class T>
    struct IsCharacter : IntegralConstant<bool, IsCharacterValue<T>>
    { };
}
#endif
