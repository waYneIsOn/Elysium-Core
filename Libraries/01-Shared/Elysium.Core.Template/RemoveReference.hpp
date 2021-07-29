/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_REMOVEREFERENCE
#define ELYSIUM_CORE_TEMPLATE_REMOVEREFERENCE

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template
{
    template <class T>
    struct RemoveReference
    {
        using Type = T;
    };

    template <class T>
    struct RemoveReference<T&>
    {
        using Type = T;
    };

    template <class T>
    struct RemoveReference<T&&>
    {
        using Type = T;
    };
    
    template <class T>
    using RemoveReferenceType = typename RemoveReference<T>::Type;
}
#endif
