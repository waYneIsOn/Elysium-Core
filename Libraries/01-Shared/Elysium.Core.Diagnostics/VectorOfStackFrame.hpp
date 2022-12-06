/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_CONTAINER_VECTOROFSTACKFRAME
#define ELYSIUM_CORE_DIAGNOSTICS_CONTAINER_VECTOROFSTACKFRAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_STACKFRAME
#include "StackFrame.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_MEMORY_DEFAULTALLOCATOROFSTACKFRAME
#include "DefaultAllocatorOfStackFrame.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Diagnostics::Container
{
	//template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<StackFrame>;

	using VectorOfStackFrame = Elysium::Core::Template::Container::Vector<StackFrame>;
}
#endif
