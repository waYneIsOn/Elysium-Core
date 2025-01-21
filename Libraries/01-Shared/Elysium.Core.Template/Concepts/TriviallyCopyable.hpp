/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_TRIVIALLYCOPYABLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_TRIVIALLYCOPYABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIALLYCOPYABLE
#include "../TypeTraits/IsTriviallyCopyable.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template <class T>
    concept TriviallyCopyable = TypeTraits::IsTriviallyCopyableValue<T>;
}
#endif
