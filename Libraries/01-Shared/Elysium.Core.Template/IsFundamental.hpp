/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_ISFUNDAMENTAL
#define ELYSIUM_CORE_TEMPLATE_ISFUNDAMENTAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISARITHMETIC
#include "IsArithemtic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISNULLPOINTER
#include "IsNullPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISVOID
#include "IsVoid.hpp"
#endif

namespace Elysium::Core::Template
{
    template <class T>
    inline constexpr bool IsFundamentalValue = IsArithmeticValue<T> || IsNullPointerValue<T> || IsVoidValue<T>;

    template <class T>
    struct IsFundamental : IntegralConstant<bool, IsFundamentalValue<T>>
    { };
}
#endif
