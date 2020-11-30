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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
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
