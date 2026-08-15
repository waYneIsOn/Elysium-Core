/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSALERTDESCRIPTION
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSALERTDESCRIPTION

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
	enum class TlsAlertDescription
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TlsAlertDescription
#else
#error "undefined os"
#endif
	{
		CloseNotify = 0,

		UnexpectedMessage = 10,

		BadRecordMAC = 20,

		DecryptionFailed = 21,

		RecordOverflow = 22,

		DecompressionFailure = 30,

		HandshakeFailure = 40,

		Ssl3NoCertificate = 41,

		BadCertificate = 42,

		UnsupportedCertificate = 43,

		CertificateRevoked = 44,

		CertificateExpired = 45,

		CertificateUnknown = 46,

		IllegalParameter = 47,

		UnknownCA = 48,

		AccessDenied = 49,

		DecodeError = 50,

		DecryptError = 51,

		ExportRestriction = 60,

		ProtocolVersion = 70,

		InsufficientSecurity = 71,

		InternalError = 80,

		InappropriateFallback = 86,

		UserCanceled = 90,

		NoRenegotiation = 100,

		MissingExtension = 109,

		UnsupportedExtension = 110,

		CertificateUnobtainable = 111,

		UnrecognizedName = 112,

		UnknownPskIdentity = 115,

		CertificateRequired = 116,

		NoApplicationProtocol = 120
	};
}
#endif
#pragma once
