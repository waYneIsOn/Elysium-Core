/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SocketType : uint32_t
#elif defined(__ANDROID__)
	enum class SocketType
#else
#error "undefined os"
#endif
	{
		Dgram,
		Raw,
		Rdm,
		Seqpacket,
		Stream,
		Unknown,
	};
}
#endif
