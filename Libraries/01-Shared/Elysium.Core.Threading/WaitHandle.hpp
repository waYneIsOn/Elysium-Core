/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_WAITHANDLE
#define ELYSIUM_CORE_THREADING_WAITHANDLE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_WAITHANDLE
#include "../Elysium.Core.Template/WaitHandle.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Threading::WaitHandle;

	using WaitHandle = Elysium::Core::Template::Threading::WaitHandle;
}
#endif
