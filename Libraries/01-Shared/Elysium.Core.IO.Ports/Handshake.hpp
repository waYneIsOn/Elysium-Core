/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PORTS_HANDSHAKE
#define ELYSIUM_CORE_IO_PORTS_HANDSHAKE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::IO::Ports
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class Handshake : uint8_t
#elif defined(__ANDROID__)
	enum class Handshake
#else
#error "undefined os"
#endif
	{
		None = 0,

		XOnXOff = 1,

		RequestToSend = 2,

		RequestToSendXOnXOff = 3,
	};
}
#endif
