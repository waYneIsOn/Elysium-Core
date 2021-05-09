/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "Array.hpp"
#endif

template class ELYSIUM_CORE_API Elysium::Core::Collections::Template::Array<Elysium::Core::byte>;
#endif
