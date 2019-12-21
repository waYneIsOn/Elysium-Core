/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_DATAROWVERSION
#define ELYSIUM_CORE_DATA_DATAROWVERSION

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Data
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class DataRowVersion : uint32_t
#elif defined(__ANDROID__)
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
