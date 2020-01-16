/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETSHUTDOWN
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETSHUTDOWN

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SocketShutdown : uint32_t
#elif defined(__ANDROID__)
	enum class SocketShutdown
#else
#error "undefined os"
#endif
	{
		Receive = 0,
		Send = 1,
		Both = 2
	};
}
#endif
