/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_VECTOROFINT32_T
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_VECTOROFINT32_T

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::int32_t>;

using VectorOfInt32_t = Elysium::Core::Template::Container::Vector<Elysium::Core::int32_t>;
#endif
