/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAINPOLICY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDCOLLECTION
#include "../Elysium.Core.Security.Cryptography.Encoding/OidCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#include "X509CertificateCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONFLAG
#include "X509RevocationFlag.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONMODE
#include "X509RevocationMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509VERIFICATIONFLAGS
#include "X509VerificationFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_DATETIME
#include "../Elysium.Core/DateTime.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_SECURITY_API X509ChainPolicy final
	{
	public:
		X509ChainPolicy();
		X509ChainPolicy(const X509ChainPolicy& Source) = delete;
		X509ChainPolicy(X509ChainPolicy&& Right) noexcept = delete;
		~X509ChainPolicy();

		X509ChainPolicy& operator=(const X509ChainPolicy& Source) = delete;
		X509ChainPolicy& operator=(X509ChainPolicy&& Right) noexcept = delete;

		const OidCollection& GetApplicationPolicy() const;
		const OidCollection& GetCertificatePolicy() const;
		const X509CertificateCollection& GetExtraStore() const;
		const X509RevocationFlag GetRevocationFlag() const;
		const X509RevocationMode GetRevocationMode() const;
		const TimeSpan GetUrlRetrievalTimeout() const;
		const X509VerificationFlags GetVerificationFlags() const;
		const DateTime GetVerificationTime() const;

		void Reset();
	private:
		OidCollection _ApplicationPolicy = OidCollection();
		OidCollection _CertificatePolicy = OidCollection();
		X509CertificateCollection _ExtraStore = X509CertificateCollection();
		X509RevocationFlag _RevocationFlag = X509RevocationFlag::EntireChain;
		X509RevocationMode _RevocationMode = X509RevocationMode::Offline;
		TimeSpan _UrlRetrievalTimeout = TimeSpan(0);
		X509VerificationFlags _VerificationFlags = X509VerificationFlags::AllFlags;
		DateTime _VerificationTime = DateTime(0);
	};
}
#endif
