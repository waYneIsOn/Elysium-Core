/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMANDTYPE
#define ELYSIUM_CORE_DATA_COMMANDTYPE

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Data
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class CommandType : uint32_t
#elif defined(__ANDROID__)
	enum class CommandType
#else
#error "undefined os"
#endif
	{
		Text = 1,
		StoredProcedure = 4,
		TableDirect = 512
	};
}
#endif
