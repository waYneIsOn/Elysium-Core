/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETTYPE
#define ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Net::Sockets
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class SocketType
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class AddressFamily
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
