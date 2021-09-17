/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_ADDREFERENCE
#define ELYSIUM_CORE_TEMPLATE_ADDREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_VOIDTYPE
#include "VoidType.hpp"
#endif

namespace Elysium::Core::Template
{
    template <class T, class = void>
    struct AddReference
    {
        using LeftValue = T;
        using RightValue = T;
    };

    template <class T>
    struct AddReference<T, VoidType<T&>>
    {
        using LeftValue = T&;
        using RightValue = T&&;
    };
}
#endif
