/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PORTS_PARITY
#define ELYSIUM_CORE_IO_PORTS_PARITY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO::Ports
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class Parity : uint8_t
#elif defined(__ANDROID__)
	enum class Parity
#else
#error "undefined os"
#endif
	{
		None = 0,

		Odd = 1,

		Even = 2,

		Mark = 3,

		Space = 4,
	};
}
#endif
