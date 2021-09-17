/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_MOVE
#define ELYSIUM_CORE_TEMPLATE_TYPETRAITS_MOVE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_REMOVEREFERENCE
#include "RemoveReference.hpp"
#endif

namespace Elysium::Core::Template::TypeTraits
{
    template<class T>
    inline constexpr RemoveReferenceType<T>&& Move(T&& Value) noexcept
    {
        return static_cast<RemoveReferenceType<T>&&>(Value);
    }
}
#endif
