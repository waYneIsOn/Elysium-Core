/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_INTERLOCKED
#define ELYSIUM_CORE_THREADING_INTERLOCKED

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_INTERLOCKED
#include "../Elysium.Core.Template/Interlocked.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Threading::Interlocked;

	using Interlocked = Elysium::Core::Template::Threading::Interlocked;
}
#endif
