/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_SEMAPHORE
#define ELYSIUM_CORE_THREADING_SEMAPHORE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_SEMAPHORE
#include "../Elysium.Core.Template/Semaphore.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Semaphore;

	using Semaphore = Elysium::Core::Template::Threading::Semaphore;
}
#endif
