/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATETIME
#define ELYSIUM_CORE_DATETIME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CHRONO_DATETIME
#include "../Elysium.Core.Template/Chrono/DateTime.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Elysium::Core::Template::Chrono::DateTime;

	using DateTime = Elysium::Core::Template::Chrono::DateTime;
}
#endif
