/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_TLSPROTOCOLS
#define ELYSIUM_CORE_SECURITY_AUTHENTICATION_TLSPROTOCOLS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TlsProtocols : uint16_t
#elif defined(__ANDROID__)
	enum class TlsProtocols
#else
#error "undefined os"
#endif
	{
		None = 0,
		Tls10 = 769,	// 0x03 0x01
		Tls11 = 770,	// 0x03 0x02
		Tls12 = 771,	// 0x03 0x03
		Tls13 = 772,	// 0x03 0x04

		Latest = Tls13
	};
	
	inline TlsProtocols operator|(TlsProtocols Left, TlsProtocols Right)
	{
		return static_cast<TlsProtocols>(static_cast<int>(Left) | static_cast<int>(Right));
	}
	inline TlsProtocols operator&(TlsProtocols Left, TlsProtocols Right)
	{
		return static_cast<TlsProtocols>(static_cast<int>(Left) & static_cast<int>(Right));
	}
}
#endif
