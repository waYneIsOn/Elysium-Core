/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SocketType : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class SocketType
#else
#error "undefined os"
#endif
	{
		//Unknown = -1,

		Stream = 1,
		Dgram = 2,
		Raw = 3,
		Rdm = 4,
		Seqpacket = 5,
	};
}
#endif
