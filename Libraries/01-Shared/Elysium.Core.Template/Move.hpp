/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVEREFERENCE
#include "RemoveReference.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
    template<class T>
    inline constexpr RemoveReferenceType<T>&& Move(T&& Value) noexcept
    {
        return static_cast<RemoveReferenceType<T>&&>(Value);
    }
}
#endif
