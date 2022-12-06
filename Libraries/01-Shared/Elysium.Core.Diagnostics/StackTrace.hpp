/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_STACKTRACE
#define ELYSIUM_CORE_DIAGNOSTICS_STACKTRACE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_MEMORY_DEFAULTALLOCATOROFSTACKFRAME
#include "DefaultAllocatorOfStackFrame.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_CONTAINER_VECTOROFSTACKFRAME
#include "VectorOfStackFrame.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKTRACE
#include "../Elysium.Core.Template/StackTrace.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Diagnostics::StackTrace;

	using StackTrace = Elysium::Core::Template::Diagnostics::StackTrace;
}
#endif
