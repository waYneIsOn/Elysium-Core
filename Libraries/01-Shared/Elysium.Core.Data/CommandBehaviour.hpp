/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMANDBEHAVIOUR
#define ELYSIUM_CORE_DATA_COMMANDBEHAVIOUR

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Data
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class CommandBehaviour : uint32_t
#elif defined(__ANDROID__)
	enum class CommandBehaviour
#else
#error "undefined os"
#endif
	{
		Default = 0,
		SingleResult = 1,
		SchemaOnly = 2,
		KeyInfo = 4,
		SingleRow = 8,
		SequentialAccess = 16,
		CloseConnection = 32
	};
}
#endif
