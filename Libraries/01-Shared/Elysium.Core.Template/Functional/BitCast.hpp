/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_BITCAST
#define ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_BITCAST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_COMPILER
#include "../System/Compiler.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIALLYCOPYABLE
#include "../TypeTraits/IsTriviallyCopyable.hpp"
#endif

namespace Elysium::Core::Template::Functional
{
    template <class To, class From>
        requires 
            (sizeof(To) == sizeof(From)) &&
            Elysium::Core::Template::TypeTraits::IsTriviallyCopyableValue<To> && 
            Elysium::Core::Template::TypeTraits::IsTriviallyCopyableValue<From>
    constexpr To BitCast(const From& Value) noexcept
    {
#if defined ELYSIUM_CORE_COMPILER_MSVC
        return __builtin_bit_cast(To, Value);
#else
#error "unhandled compiler in Elysium::Core::Template::Functional::BitCast<To, From>(const From& Value)"
#endif
    }
}
#endif
