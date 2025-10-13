/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_REFLECTION_CONTAINER_VECTOROFMODULEPOINTER
#define ELYSIUM_CORE_REFLECTION_CONTAINER_VECTOROFMODULEPOINTER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_MEMORY_DEFAULTALLOCATOROFMODULEPOINTER
#include "../Memory/DefaultAllocatorOfModulePointer.hpp"
#endif

namespace Elysium::Core::Reflection::Container
{
	template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<const Module*>;

	using VectorOfConstModulePointer = Elysium::Core::Template::Container::Vector<const Module*>;
}
#endif
