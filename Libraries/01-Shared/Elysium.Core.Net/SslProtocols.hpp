/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_SSLPROTOCOLS
#define ELYSIUM_CORE_NET_SECURITY_SSLPROTOCOLS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SslProtocols : uint32_t
#elif defined(__ANDROID__)
	enum class SslProtocols
#else
#error "undefined os"
#endif
	{
		Default = 240,
		None = 0,
		Ssl2 = 12,
		Ssl3 = 48,
		Tls = 192,
		Tls11 = 768,
		Tls12 = 3072,
		Tls13 = 12288
	};

	inline SslProtocols operator|(SslProtocols Left, SslProtocols Right)
	{
		return static_cast<SslProtocols>(static_cast<int>(Left) | static_cast<int>(Right));
	}
	inline SslProtocols operator&(SslProtocols Left, SslProtocols Right)
	{
		return static_cast<SslProtocols>(static_cast<int>(Left) & static_cast<int>(Right));
	}
}
#endif
