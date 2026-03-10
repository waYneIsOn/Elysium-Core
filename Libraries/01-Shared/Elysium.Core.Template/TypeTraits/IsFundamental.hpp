/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFUNDAMENTAL
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFUNDAMENTAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISARITHMETIC
#include "IsArithemtic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNULLPOINTER
#include "IsNullPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOID
#include "IsVoid.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    inline constexpr bool IsFundamentalValue = IsArithmeticValue<T> || IsNullPointerValue<T> || IsVoidValue<T>;

    template <class T>
    struct IsFundamental : IntegralConstant<bool, IsFundamentalValue<T>>
    { };
}
#endif
