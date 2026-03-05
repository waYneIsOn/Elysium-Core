/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MATH_FACTORIAL
#define ELYSIUM_CORE_TEMPLATE_MATH_FACTORIAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

namespace Elysium::Core::Template::Math
{
    template <Concepts::Integer I, I Input>
    struct Factorial
    {
        static constexpr const I Result = Input * Factorial<Input - 1>::Result;
    };

    template <>
    struct Factorial<System::uint8_t, 0>
    {
        static constexpr const System::uint8_t Result = 1;
    };

    template <>
    struct Factorial<System::uint16_t, 0>
    {
        static constexpr const System::uint16_t Result = 1;
    };

    template <>
    struct Factorial<System::uint32_t, 0>
    {
        static constexpr const System::uint32_t Result = 1;
    };

    template <>
    struct Factorial<System::uint64_t, 0>
    {
        static constexpr const System::uint64_t Result = 1;
    };

    template <>
    struct Factorial<System::int8_t, 0>
    {
        static constexpr const System::uint8_t Result = 1;
    };

    template <>
    struct Factorial<System::int16_t, 0>
    {
        static constexpr const System::int16_t Result = 1;
    };

    template <>
    struct Factorial<System::int32_t, 0>
    {
        static constexpr const System::int32_t Result = 1;
    };

    template <>
    struct Factorial<System::int64_t, 0>
    {
        static constexpr const System::int64_t Result = 1;
    };
}
#endif
