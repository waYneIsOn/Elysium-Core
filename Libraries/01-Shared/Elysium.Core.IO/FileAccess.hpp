/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_FILEACCESS
#define ELYSIUM_CORE_IO_FILEACCESS

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::IO
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class FileAccess : uint32_t
#elif defined(__ANDROID__)
	enum class FileAccess
#else
#error "undefined os"
#endif
	{
		Read = 1,
		Write = 2,
		ReadWrite = 3
	};
}
#endif
