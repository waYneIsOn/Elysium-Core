/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <bool Condition, class TrueType, class FalseType>
    struct Conditional
    {
        using Type = TrueType;
    };

    template <class TrueType, class FalseType>
    struct Conditional<false, TrueType, FalseType>
    {
        using Type = FalseType;
    };

    template <bool Condition, class TrueType, class FalseType>
    using ConditionalType = typename Conditional<Condition, TrueType, FalseType>::Type;
}
#endif
