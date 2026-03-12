/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_DATAROWVERSION
#define ELYSIUM_CORE_DATA_DATAROWVERSION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Data
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class DataRowVersion 
		: Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class DataRowVersion
#else
#error "undefined os"
#endif
	{
		Original = 256,

		Current = 512,

		Proposed = 1024,

		Default = 1536
	};
}
#endif
