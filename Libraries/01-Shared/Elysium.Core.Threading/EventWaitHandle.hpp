/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_EVENTWAITHANDLE
#define ELYSIUM_CORE_THREADING_EVENTWAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_EVENTWAITHANDLE
#include "../Elysium.Core.Template/EventWaitHandle.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Threading::EventWaitHandle;

	using EventWaitHandle = Elysium::Core::Template::Threading::EventWaitHandle;
}
#endif
