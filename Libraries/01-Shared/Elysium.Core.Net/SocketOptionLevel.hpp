/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETOPTIONLEVEL
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETOPTIONLEVEL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SocketOptionLevel : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class SocketOptionLevel
#else
#error "undefined os"
#endif
	{
		IP = 0,

		Tcp = 6,

		Udp = 17,

		IPv6 = 41,

		Socket = 65535
	};
}

#endif
