/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_MUTEX
#define ELYSIUM_CORE_THREADING_MUTEX

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_MUTEX
#include "../Elysium.Core.Template/Mutex.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Mutex;

	using Mutex = Elysium::Core::Template::Threading::Mutex;
}
#endif
