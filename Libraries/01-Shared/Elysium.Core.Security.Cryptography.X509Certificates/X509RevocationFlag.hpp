/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONFLAG
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONFLAG

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class X509RevocationFlag : uint32_t
#elif defined(__ANDROID__)
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
