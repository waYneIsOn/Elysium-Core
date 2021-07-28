/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ADDCONSTANT
#define ELYSIUM_CORE_TEMPLATE_ADDCONSTANT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONDITIONAL
#include "Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ISCONSTANT
#include "IsConstant.hpp"
#endif

namespace Elysium::Core::Template
{
    template <class T>
    struct AddConstant
    {
        using Type = Conditional<IsConstant<T>::Value, T, const T>::Type;
    };

    template <class T>
    using AddConstantType = typename AddConstant<T>::Type;
}
#endif
