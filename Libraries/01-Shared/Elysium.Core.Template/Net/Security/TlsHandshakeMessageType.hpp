/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSHANDSHAKEMESSAGETYPE
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSHANDSHAKEMESSAGETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Net::Security
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class TlsHandshakeMessageType
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TlsHandshakeMessageType
#else
#error "undefined os"
#endif
	{
		ClientHello = 0x01,

		ServerHello = 0x02,

		ClientKeyExchange = 0x10,

		Certificate = 0x0B,

		ServerKeyExchange = 0x0C,

		ServerHelloDone = 0x0E,

		Finished = 0x14,
	};
}
#endif
#pragma once
