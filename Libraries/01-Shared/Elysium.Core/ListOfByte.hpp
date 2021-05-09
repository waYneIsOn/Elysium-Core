/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LISTOFBYTE
#define ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LISTOFBYTE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

template class ELYSIUM_CORE_API Elysium::Core::Collections::Template::List<Elysium::Core::byte>;
#endif
