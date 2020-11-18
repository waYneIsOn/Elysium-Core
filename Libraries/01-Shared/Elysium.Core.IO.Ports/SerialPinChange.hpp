/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PORTS_SERIALPINCHANGE
#define ELYSIUM_CORE_IO_PORTS_SERIALPINCHANGE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO::Ports
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SerialPinChange : uint8_t
#elif defined(__ANDROID__)
	enum class SerialPinChange
#else
#error "undefined os"
#endif
	{
		CtsChanged = 8,

		DsrChanged = 16,

		CDChanged = 32,

		Break = 64,

		Ring = 256,
	};
}
#endif
