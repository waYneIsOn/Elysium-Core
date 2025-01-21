/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIALLYCOPYABLE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIALLYCOPYABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <class T>
    struct IsTriviallyCopyable : IntegralConstant<bool, __is_trivially_copyable(T)>
    {
    };

    template <class T>
    inline constexpr bool IsTriviallyCopyableValue = __is_trivially_copyable(T);
}
#endif
