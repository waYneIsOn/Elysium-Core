/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#define ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_REMOVECONSTVOLATILE
#include "../Functional/RemoveConstVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "../TypeTraits/IsAnyOf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Concepts
{
    template<class T>
    concept HuffmanCodeable = Elysium::Core::Template::TypeTraits::IsAnyOfValue<Functional::RemoveConstVolatileType<T>,
        Elysium::Core::Template::System::byte>;
}
#endif
