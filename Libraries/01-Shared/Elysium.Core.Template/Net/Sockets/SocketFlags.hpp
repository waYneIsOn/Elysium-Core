/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETFLAGS
#define ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETFLAGS

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
	enum class SocketFlags
		: Elysium::Core::Template::System::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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

	inline SocketFlags operator|(const SocketFlags Left, const SocketFlags Right)
	{
		return static_cast<SocketFlags>(static_cast<Elysium::Core::Template::System::uint16_t>(Left) | static_cast<Elysium::Core::Template::System::uint16_t>(Right));
	}

	inline SocketFlags operator&(const SocketFlags Left, const SocketFlags Right)
	{
		return static_cast<SocketFlags>(static_cast<Elysium::Core::Template::System::uint16_t>(Left) & static_cast<Elysium::Core::Template::System::uint16_t>(Right));
	}
}
#endif
