/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_AUTORESETEVENT
#define ELYSIUM_CORE_THREADING_AUTORESETEVENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_AUTORESETEVENT
#include "../Elysium.Core.Template/AutoResetEvent.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Threading::AutoResetEvent;

	using AutoResetEvent = Elysium::Core::Template::Threading::AutoResetEvent;
}
#endif
