/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVECONSTRUCTIBLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVECONSTRUCTIBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVECONSTRUCTIBLE
#include "IsMoveConstructible.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template <class T>
    concept MoveConstructible = TypeTraits::IsMoveConstructibleValue<T>;
}
#endif
