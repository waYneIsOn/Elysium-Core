/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNOTHROWDEFAULTCONSTRUCTIBLE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNOTHROWDEFAULTCONSTRUCTIBLE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsNoThrowDefaultConstructibleValue = __is_nothrow_constructible(T);

    template <class T>
    struct IsNoThrowDefaultConstructible : IntegralConstant<bool, IsNoThrowDefaultConstructibleValue<T>>
    { };
}
#endif
