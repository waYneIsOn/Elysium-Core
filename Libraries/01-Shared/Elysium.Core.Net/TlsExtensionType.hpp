/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_TLSEXTENSIONTYPE
#define ELYSIUM_CORE_NET_SECURITY_TLSEXTENSIONTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TlsExtensionType : uint16_t
#elif defined(__ANDROID__)
	enum class TlsExtensionType
#else
#error "undefined os"
#endif
	{
		ServerName = 0,
		MaxFragmentLength = 1,
		ClientCertificateUrl = 2,
		TrustedCAKeys = 3,
		TrruncatedHMAC = 4,
		StatusRequest = 5,
		UserMapping = 6,
		ClientAuthZ = 7,
		ServerAuthZ = 8,
		CertificateType = 9,
		SupportedGroupds = 10,	// EllipticCurves
		ECPointFormats = 11,
		Srp = 12,
		SignatureAlgorithms = 13,
		UseSrtp = 14,
		Heartbeat = 15,
		ApplicationLayerProtocolNegotiation = 16,
		StatusRequestV2 = 17,
		SignedCertificateTimestamp = 18,
		ClientCertificateType = 19,
		ServerCertificateType = 20,
		Padding = 21,
		EncryptThenMac = 22,
		ExtendedMasterSecret = 23,
		TokenBinding = 24,
		CachedInfo = 25,
		TlsLts = 26,
		CompressCertificate = 27,
		RecordSizeLimit = 28,
		PasswordProtect = 29,
		PasswordClear = 30,
		PasswordSalt = 31,
		TicketPinning = 32,
		TlsCertificateWithExternalPsk = 33,
		DelegatedCredentials = 34,
		SessionTicket = 35,	// SessionTicketTLS
		PreSharedKey = 41,
		EarlyData = 42,
		SupportedVersions = 43,
		Cookie = 44,
		PskKeyExchangeModes = 45,
		CertificateAuthorities = 47,
		OidFilters = 48,
		PostHandshakeAuthentication = 49,
		SignatureAlgorithmsCertificate = 50,
		KeyShare = 51,
		TransparencyInfo = 52,
		ConnectionId = 53,
		ExternalIdHash = 55,
		ExternalSessionId = 56,
		RenegotiationInfo = 65281
	};
}
#endif



