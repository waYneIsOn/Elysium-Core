/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_MANUALRESETEVENT
#define ELYSIUM_CORE_THREADING_MANUALRESETEVENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MANUALRESETEVENT
#include "../Elysium.Core.Template/ManualResetEvent.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Threading::ManualResetEvent;

	using ManualResetEvent = Elysium::Core::Template::Threading::ManualResetEvent;
}
#endif
