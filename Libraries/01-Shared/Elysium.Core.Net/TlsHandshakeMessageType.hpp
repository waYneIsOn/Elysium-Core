/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_TLSHANDSHAKEMESSAGETYPE
#define ELYSIUM_CORE_NET_SECURITY_TLSHANDSHAKEMESSAGETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TlsHandshakeMessageType : uint8_t
#elif defined(__ANDROID__)
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
