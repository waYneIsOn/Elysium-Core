/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_SEEKORIGIN
#define ELYSIUM_CORE_IO_SEEKORIGIN

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::IO
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SeekOrigin : uint32_t
#elif defined(__ANDROID__)
	enum class SeekOrigin
#else
#error "undefined os"
#endif
	{
		Begin = 0,
		Current = 1,
		End = 2
	};
}
#endif
