/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DIAGNOSTICS_PROCESS
#define ELYSIUM_CORE_DIAGNOSTICS_PROCESS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_DIAGNOSTICS_CONTAINER_VECTOROFPROCESS
#include "VectorOfProcess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_PROCESS
#include "../Elysium.Core.Template/Process.hpp"
#endif

namespace Elysium::Core::Diagnostics
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Diagnostics::Process;

	using Process = Elysium::Core::Template::Diagnostics::Process;
}
#endif
