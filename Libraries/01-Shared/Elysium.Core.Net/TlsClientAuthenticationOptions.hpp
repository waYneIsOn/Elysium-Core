/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCLIENTAUTHENTICATIONOPTIONS
#define ELYSIUM_CORE_NET_SECURITY_TLSCLIENTAUTHENTICATIONOPTIONS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../Elysium.Core.Security/X509Chain.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSPOLICYERRORS
#include "TlsPolicyErrors.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCIPHERSUITE
#include "TlsCipherSuite.hpp"
#endif

namespace Elysium::Core::Net::Security
{
#define RemoteCertificateValidationCallback Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::TlsPolicyErrors>
#define LocalCertificateSelectionCallback Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Collections::Template::Array<String>&>

	class ELYSIUM_CORE_NET_API TlsClientAuthenticationOptions sealed
	{
	public:
		TlsClientAuthenticationOptions(const bool AllowRenegotiation, const Collections::Template::Array<TlsCipherSuite>& AllowedCipherSuites, const RemoteCertificateValidationCallback* UserCertificateValidationCallback, const LocalCertificateSelectionCallback* UserCertificateSelectionCallback);
		TlsClientAuthenticationOptions(const TlsClientAuthenticationOptions& Source);
		TlsClientAuthenticationOptions(TlsClientAuthenticationOptions&& Right) noexcept = delete;
		~TlsClientAuthenticationOptions();

		TlsClientAuthenticationOptions& operator=(const TlsClientAuthenticationOptions& Source);
		TlsClientAuthenticationOptions& operator=(TlsClientAuthenticationOptions&& Right) noexcept = delete;

		const Collections::Template::Array<TlsCipherSuite>& GetAllowedCipherSuites() const;
	private:
		bool _AllowRenegotiation;
		Collections::Template::Array<TlsCipherSuite> _AllowedCipherSuites;
		// _ClientCertificates;
		// _EnabledTlsProtocols;
	};
}
#endif
