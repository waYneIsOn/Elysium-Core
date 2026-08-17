/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TIMESPAN
#define ELYSIUM_CORE_TIMESPAN

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_TIMESPAN
#include "../Elysium.Core.Template/Chrono/TimeSpan.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Chrono::TimeSpan;

	using TimeSpan = Elysium::Core::Template::Chrono::TimeSpan;
}
#endif
