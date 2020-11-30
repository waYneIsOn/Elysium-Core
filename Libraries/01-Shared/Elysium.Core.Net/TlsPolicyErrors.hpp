/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_TLSPOLICYERRORS
#define ELYSIUM_CORE_NET_SECURITY_TLSPOLICYERRORS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TlsPolicyErrors : uint32_t
#elif defined(__ANDROID__)
	enum class TlsPolicyErrors
#else
#error "undefined os"
#endif
	{
		None = 0,
		RemoteCertificateNotAvailable = 1,
		RemoteCertificateNameMismatch = 2,
		RemoteCertificateChainErrors = 4
	};

	inline TlsPolicyErrors operator|(TlsPolicyErrors Left, TlsPolicyErrors Right)
	{
		return static_cast<TlsPolicyErrors>(static_cast<int>(Left) | static_cast<int>(Right));
	}
	inline TlsPolicyErrors operator&(TlsPolicyErrors Left, TlsPolicyErrors Right)
	{
		return static_cast<TlsPolicyErrors>(static_cast<int>(Left) & static_cast<int>(Right));
	}
}
#endif
