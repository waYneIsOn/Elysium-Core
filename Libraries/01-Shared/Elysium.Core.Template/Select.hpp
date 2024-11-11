/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_SELECT
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_SELECT

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template <bool>
    struct Select 
    {
        template <class T, class>
        using Apply = T;
    };

    template <>
    struct Select<false> 
    {
        template <class, class T>
        using Apply = T;
    };

}
#endif
