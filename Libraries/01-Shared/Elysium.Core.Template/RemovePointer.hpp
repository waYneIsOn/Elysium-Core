/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVERPOINTER
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVERPOINTER

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Functional
{
    template <class T>
    struct RemovePointer
    {
        using Type = T;
    };

    template <class T>
    struct RemovePointer<T*>
    {
        using Type = T;
    };

    template <class T>
    struct RemovePointer<T**>
    {
        using Type = T;
    };

    template <class T>
    using RemovePointerType = typename RemovePointer<T>::Type;
}
#endif
