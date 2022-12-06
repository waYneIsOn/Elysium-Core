/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_MEMORY_DEFAULTALLOCATOROFSTACKFRAME
#define ELYSIUM_CORE_DIAGNOSTICS_MEMORY_DEFAULTALLOCATOROFSTACKFRAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_STACKFRAME
#include "StackFrame.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Diagnostics::Memory
{
	//template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<StackFrame>;

	using DefaultAllocatorOfStackFrame = Elysium::Core::Template::Memory::DefaultAllocator<StackFrame>;

}
#endif
