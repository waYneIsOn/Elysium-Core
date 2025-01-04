/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFSTRING
#include "../Elysium.Core/VectorOfString.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CHAIN
#include "../Elysium.Core.Security.Cryptography.X509Certificates/X509Chain.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSPOLICYERRORS
#include "TlsPolicyErrors.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCIPHERSUITE
#include "TlsCipherSuite.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Elysium.Core.Template/Vector.hpp"
#endif

namespace Elysium::Core::Net::Security
{
	class ELYSIUM_CORE_NET_API TlsClientAuthenticationOptions final
	{
	public:
		TlsClientAuthenticationOptions(const bool AllowRenegotiation, const Elysium::Core::Template::Container::Vector<TlsCipherSuite>& AllowedCipherSuites);

		TlsClientAuthenticationOptions(const bool AllowRenegotiation, const Elysium::Core::Template::Container::Vector<TlsCipherSuite>& AllowedCipherSuites,
			Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::TlsPolicyErrors>& UserCertificateValidationCallback,
			Elysium::Core::Template::Container::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::Utf8String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Container::VectorOfUtf8String&>& UserCertificateSelectionCallback);
		
		TlsClientAuthenticationOptions(const TlsClientAuthenticationOptions& Source);

		TlsClientAuthenticationOptions(TlsClientAuthenticationOptions&& Right) noexcept = delete;

		~TlsClientAuthenticationOptions();
	public:
		TlsClientAuthenticationOptions& operator=(const TlsClientAuthenticationOptions& Source);

		TlsClientAuthenticationOptions& operator=(TlsClientAuthenticationOptions&& Right) noexcept = delete;
	public:
		const Elysium::Core::Template::Container::Vector<TlsCipherSuite>& GetAllowedCipherSuites() const;

		const Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::TlsPolicyErrors>& GetUserCertificateValidationCallback() const;
		
		const Elysium::Core::Template::Container::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::Utf8String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Container::VectorOfUtf8String&>& GetUserCertificateSelectionCallback() const;
	private:
		bool _AllowRenegotiation;
		Elysium::Core::Template::Container::Vector<TlsCipherSuite> _AllowedCipherSuites;
		Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::TlsPolicyErrors> _UserCertificateValidationCallback;
		Elysium::Core::Template::Container::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::Utf8String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Container::VectorOfUtf8String&> _UserCertificateSelectionCallback;
		// _ClientCertificates;
		// _EnabledTlsProtocols;
	private:
		static const bool ValidateServerCertificate(const void* Sender, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& Certificate, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain& Chain, const TlsPolicyErrors PolicyErrors);
		
		static const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& SelectLocalCertificate(const void* Sender, const Elysium::Core::Utf8String& TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection& LocalCertificates, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate& RemoteCertificate, const Elysium::Core::Container::VectorOfUtf8String& AcceptableIssuers);
	};
}
#endif
