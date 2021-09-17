/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_REMOVERPOINTER
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_REMOVERPOINTER

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
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
