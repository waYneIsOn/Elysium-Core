/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_CONTAINER_VECTOROFPROCESS
#define ELYSIUM_CORE_DIAGNOSTICS_CONTAINER_VECTOROFPROCESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS
#include "../Elysium.Core.Template/Process.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_MEMORY_DEFAULTALLOCATOROFPROCESS
#include "DefaultAllocatorOfProcess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Diagnostics::Container
{
	//template class ELYSIUM_CORE_API Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Diagnostics::Process>;

	using VectorOfProcess = Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Diagnostics::Process>;
}
#endif
