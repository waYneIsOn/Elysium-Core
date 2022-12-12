/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONFLAG
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONFLAG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class X509RevocationFlag : uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class X509RevocationFlag
#else
#error "undefined os"
#endif
	{
		EndCertificateOnly = 0,
		EntireChain = 1,
		ExcludeRoot = 2,
	};
}
#endif
