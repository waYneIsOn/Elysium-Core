/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETFLAGS
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETFLAGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SocketFlags : Elysium::Core::int32_t
#elif defined(__ANDROID__)
	enum class SocketFlags
#else
#error "undefined os"
#endif
	{
		None = 0,
		OutOfBand = 1,
		Peek = 2,
		DontRoute = 4,
		Truncated = 256,
		ControlDataTruncated = 512,
		Broadcast = 1024,
		Multicast = 2048,
		Partial = 32768,
	};

	inline SocketFlags operator|(SocketFlags Left, SocketFlags Right)
	{
		return static_cast<SocketFlags>(static_cast<int>(Left) | static_cast<int>(Right));
	}
	inline SocketFlags operator&(SocketFlags Left, SocketFlags Right)
	{
		return static_cast<SocketFlags>(static_cast<int>(Left) & static_cast<int>(Right));
	}
}
#endif
