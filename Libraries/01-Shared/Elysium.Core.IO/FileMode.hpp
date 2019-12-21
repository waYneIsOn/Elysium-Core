/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_FILEMODE
#define ELYSIUM_CORE_IO_FILEMODE

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::IO
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class FileMode : uint32_t
#elif defined(__ANDROID__)
	enum class FileMode
#else
#error "undefined os"
#endif
	{
		CreateNew = 1,
		Create = 2,
		Open = 3,
		OpenOrCreate = 4,
		Truncate = 5,
		Append = 6
	};
}
#endif
