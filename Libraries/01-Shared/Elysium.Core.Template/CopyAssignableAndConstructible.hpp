/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COPYASSIGNABLEANDCONSTRUCTIBLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_COPYASSIGNABLEANDCONSTRUCTIBLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOPYASSIGNABLE
#include "IsCopyAssignable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOPYCONSTRUCTIBLE
#include "IsCopyConstructible.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template <class T>
    concept CopyAssignableAndConstructible = TypeTraits::IsCopyAssignableValue<T> && TypeTraits::IsCopyConstructibleValue<T>;
}
#endif
