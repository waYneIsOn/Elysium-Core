/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_TRIVIAL
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_TRIVIAL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOMPLETELYDEFINED
#include "../TypeTraits/IsCompletelyDefined.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIAL
#include "../TypeTraits/IsTrivial.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template <class T>
    //concept Trivial = TypeTraits::IsCompletelyDefinedValue<T> && TypeTraits::IsTrivialValue<T>;
    concept Trivial = TypeTraits::IsTrivialValue<T>;
}
#endif
