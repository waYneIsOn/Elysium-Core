/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_DISJUNCTION
#define ELYSIUM_CORE_TEMPLATE_DISJUNCTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
{
    template <bool IsFirstValue, class First, class... Rest>
    struct _Disjunction
    {
        using Type = First;
    };

    template <class FirstFalse, class Second, class... Rest>
    struct _Disjunction<false, FirstFalse, Second, Rest...>
    {
        using Type = typename _Disjunction<Second::Value, Second, Rest...>::Type;
    };
    
    template <class... Types>
    struct Disjunction : IntegralConstant<bool, false>
    { };
    
    template <class First, class... Rest>
    struct Disjunction<First, Rest...> : _Disjunction<First::Value, First, Rest...>::Type
    { };

    template <class... Types>
    inline constexpr bool DisjunctionValue = Disjunction<Types...>::Value;
}
#endif
