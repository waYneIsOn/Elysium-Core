/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_SSLPOLICYERRORS
#define ELYSIUM_CORE_NET_SECURITY_SSLPOLICYERRORS

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SslPolicyErrors : uint32_t
#elif defined(__ANDROID__)
	enum class SslPolicyErrors
#else
#error "undefined os"
#endif
	{
		None = 0,
		RemoteCertificateNotAvailable = 1,
		RemoteCertificateNameMismatch = 2,
		RemoteCertificateChainErrors = 4
	};

	inline SslPolicyErrors operator|(SslPolicyErrors lhs, SslPolicyErrors rhs)
	{
		return static_cast<SslPolicyErrors>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}
	inline SslPolicyErrors operator&(SslPolicyErrors lhs, SslPolicyErrors rhs)
	{
		return static_cast<SslPolicyErrors>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}
}
#endif
