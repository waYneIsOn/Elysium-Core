/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509VERIFICATIONFLAGS
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509VERIFICATIONFLAGS

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
	enum class X509VerificationFlags : Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class X509VerificationFlags
#else
#error "undefined os"
#endif
	{
		NoFlag = 0,
		IgnoreNotTimeValid = 1,
		IgnoreNotTimeNested = 4,
		IgnoreInvalidBasicConstraints = 8,
		AllowUnknownCertificateAuthority = 16,
		IgnoreWrongUsage = 32,
		IgnoreInvalidName = 64,
		IgnoreInvalidPolicy = 128,
		IgnoreEndRevocationUnknown = 256,
		IgnoreCtlSignerRevocationUnknown = 512,
		IgnoreCertificateAuthorityRevocationUnknown = 1024,
		IgnoreRootRevocationUnknown = 2048,

		AllFlags = NoFlag | IgnoreNotTimeValid | IgnoreNotTimeNested | IgnoreInvalidBasicConstraints | AllowUnknownCertificateAuthority | IgnoreWrongUsage | IgnoreInvalidName |
		IgnoreInvalidPolicy | IgnoreEndRevocationUnknown | IgnoreCtlSignerRevocationUnknown | IgnoreCertificateAuthorityRevocationUnknown | IgnoreRootRevocationUnknown,
	};

	inline X509VerificationFlags operator|(X509VerificationFlags Left, X509VerificationFlags Right)
	{
		return static_cast<X509VerificationFlags>(static_cast<uint32_t>(Left) | static_cast<uint32_t>(Right));
	}
	inline X509VerificationFlags operator&(X509VerificationFlags Left, X509VerificationFlags Right)
	{
		return static_cast<X509VerificationFlags>(static_cast<uint32_t>(Left) & static_cast<uint32_t>(Right));
	}
}
#endif
