/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PORTS_SERIALERROR
#define ELYSIUM_CORE_IO_PORTS_SERIALERROR

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO::Ports
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SerialError : uint8_t
#elif defined(__ANDROID__)
	enum class SerialError
#else
#error "undefined os"
#endif
	{
		RXOver = 1,

		Overrun = 2,

		RXParity = 4,

		Frame = 8,

		TXFULL = 256
	};
}
#endif
