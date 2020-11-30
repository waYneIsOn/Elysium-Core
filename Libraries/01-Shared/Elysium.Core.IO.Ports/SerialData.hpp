/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PORTS_SERIALDATA
#define ELYSIUM_CORE_IO_PORTS_SERIALDATA

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO::Ports
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SerialData : uint8_t
#elif defined(__ANDROID__)
	enum class SerialData
#else
#error "undefined os"
#endif
	{
		Chars = 1,

		Eof = 2,
	};
}
#endif
