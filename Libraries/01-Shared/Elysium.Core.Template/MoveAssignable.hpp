/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVEASSIGNABLE
#include "IsMoveAssignable.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template <class T>
    concept MoveAssignable = TypeTraits::IsMoveAssignableValue<T>;
}
#endif
