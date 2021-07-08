/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONDITIONAL
#define ELYSIUM_CORE_TEMPLATE_CONDITIONAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_INTEGRALCONSTANT
#include "IntegralConstant.hpp"
#endif

namespace Elysium::Core::Template
{
    template <bool _Test, class _Ty1, class _Ty2>
    struct Conditional
    {
        using Type = _Ty1;
    };

    template <class _Ty1, class _Ty2>
    struct Conditional<false, _Ty1, _Ty2>
    {
        using Type = _Ty2;
    };

    template <bool _Test, class _Ty1, class _Ty2>
    using ConditionalType = typename Conditional<_Test, _Ty1, _Ty2>::Type;
}
#endif
