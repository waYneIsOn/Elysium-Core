/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_ADDCONSTANT
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_ADDCONSTANT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONSTANT
#include "IsConstant.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
    template <class T>
    struct AddConstant
    {
        using Type = Elysium::Core::Template::TypeTraits::ConditionalType<Elysium::Core::Template::TypeTraits::IsConstant<T>::Value, T, const T>;
    };

    template <class T>
    using AddConstantType = typename AddConstant<T>::Type;
}
#endif
