/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_MEMORY_DEFAULTALLOCATOROFTYPEPOINTER
#define ELYSIUM_CORE_REFLECTION_MEMORY_DEFAULTALLOCATOROFTYPEPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Reflection
{
	class Type;
}

namespace Elysium::Core::Reflection::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<const Type*>;

	using DefaultAllocatorOfConstTypePointer = Elysium::Core::Template::Memory::DefaultAllocator<const Type*>;
}
#endif
