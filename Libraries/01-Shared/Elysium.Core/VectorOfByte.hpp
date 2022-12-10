/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#define ELYSIUM_CORE_CONTAINER_VECTOROFBYTE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_MEMORY_DEFAULTALLOCATOROFBYTE
#include "DefaultAllocatorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::byte>;

	using VectorOfByte = Elysium::Core::Template::Container::Vector<Elysium::Core::byte, Memory::DefaultAllocatorOfByte>;
}
#endif
