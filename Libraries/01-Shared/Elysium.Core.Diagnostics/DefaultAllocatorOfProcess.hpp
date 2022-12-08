/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_MEMORY_DEFAULTALLOCATOROFPROCESS
#define ELYSIUM_CORE_DIAGNOSTICS_MEMORY_DEFAULTALLOCATOROFPROCESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS
#include "../Elysium.Core.Template/Process.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTALLOCATOR
#include "../Elysium.Core.Template/DefaultAllocator.hpp"
#endif

namespace Elysium::Core::Diagnostics::Memory
{
	//template class ELYSIUM_CORE_API Elysium::Core::Template::Memory::DefaultAllocator<Elysium::Core::Template::Diagnostics::Process>;

	using DefaultAllocatorOfProcess = Elysium::Core::Template::Memory::DefaultAllocator<Elysium::Core::Template::Diagnostics::Process>;
}
#endif
