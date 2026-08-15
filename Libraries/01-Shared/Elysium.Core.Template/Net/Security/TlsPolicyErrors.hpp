/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSPOLICYERRORS
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSPOLICYERRORS

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
	enum class TlsPolicyErrors
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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

	inline TlsPolicyErrors operator|(const TlsPolicyErrors Left, const TlsPolicyErrors Right)
	{
		return static_cast<TlsPolicyErrors>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) | static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}

	inline TlsPolicyErrors operator&(const TlsPolicyErrors Left, const TlsPolicyErrors Right)
	{
		return static_cast<TlsPolicyErrors>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) & static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}
}
#endif
