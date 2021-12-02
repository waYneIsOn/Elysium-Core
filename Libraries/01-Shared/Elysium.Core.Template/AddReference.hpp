/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_ADDREFERENCE
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_ADDREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_VOIDTYPE
#include "VoidType.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
    template <class T, class = void>
    struct AddReference
    {
        using LeftValue = T;
        using RightValue = T;
    };

    template <class T>
    struct AddReference<T, TypeTraits::VoidType<T&>>
    {
        using LeftValue = T&;
        using RightValue = T&&;
    };
}
#endif
