/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PORTS_STOPBITS
#define ELYSIUM_CORE_IO_PORTS_STOPBITS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO::Ports
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class StopBits : uint8_t
#elif defined(__ANDROID__)
	enum class StopBits
#else
#error "undefined os"
#endif
	{
		None = 0,

		One = 1,

		Two = 2,

		OnePointFive = 3,
	};
}
#endif
