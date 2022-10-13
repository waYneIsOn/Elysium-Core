/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_VECTOROFBYTE
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_VECTOROFBYTE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::byte>;

using VectorOfByte = Elysium::Core::Template::Container::Vector<Elysium::Core::byte>;
#endif
