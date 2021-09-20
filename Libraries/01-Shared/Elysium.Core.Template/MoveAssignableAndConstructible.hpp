/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLEANDCONSTRUCTIBLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLEANDCONSTRUCTIBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVEASSIGNABLE
#include "IsMoveAssignable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVECONSTRUCTIBLE
#include "IsMoveConstructible.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template <class T>
    concept MoveAssignableAndConstructible = TypeTraits::IsMoveAssignableValue<T> && TypeTraits::IsMoveConstructibleValue<T>;
}
#endif
