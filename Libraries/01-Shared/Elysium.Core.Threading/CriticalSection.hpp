/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_THREADING_CRITICALSECTION
#define ELYSIUM_CORE_THREADING_CRITICALSECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_CRITICALSECTION
#include "../Elysium.Core.Template/CriticalSection.hpp"
#endif

namespace Elysium::Core::Threading
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Threading::CriticalSection;

	using CriticalSection = Elysium::Core::Template::Threading::CriticalSection;
}
#endif
