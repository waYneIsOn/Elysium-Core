/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSAUTHENTICATIONOPTIONS
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSAUTHENTICATIONOPTIONS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../../Container/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSCIPHERSUITE
#include "TlsCipherSuite.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSPOLICYERRORS
#include "TlsPolicyErrors.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "../../Security/Cryptography/X509Certificates/X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../Text/StringView.hpp"
#endif

namespace Elysium::Core::Template::Net::Security
{
	class TlsClientAuthenticationOptions
	{
	public:
		constexpr TlsClientAuthenticationOptions() = delete;
		
		inline constexpr TlsClientAuthenticationOptions(const bool AllowRenegotiation, 
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::Security::TlsCipherSuite>& AllowedCipherSuites)
			: _AllowRenegotiation(AllowRenegotiation), _AllowedCipherSuites(AllowedCipherSuites),
			_UserCertificateValidationCallback(
				Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&,
				const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Chain&,
				const Elysium::Core::Template::Net::Security::TlsPolicyErrors>::Bind<&TlsClientAuthenticationOptions::ValidateServerCertificate>()),
			_UserCertificateSelectionCallback(
				Elysium::Core::Template::Container::Delegate<const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&, const void*,
				const Elysium::Core::Template::Text::StringView<char8_t>,
				const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>&,
				const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&,
				const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>&>::Bind<&TlsClientAuthenticationOptions::SelectLocalCertificate>())
		{ }
		
		inline constexpr TlsClientAuthenticationOptions(const bool AllowRenegotiation, 
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::Security::TlsCipherSuite>& AllowedCipherSuites,
			Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&,
				const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Chain&, 
				const Elysium::Core::Template::Net::Security::TlsPolicyErrors>& UserCertificateValidationCallback,
			Elysium::Core::Template::Container::Delegate<const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&, const void*, 
				const Elysium::Core::Template::Text::StringView<char8_t>,
				const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>&, 
				const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&, 
				const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>&>& UserCertificateSelectionCallback)
			: _AllowRenegotiation(AllowRenegotiation), _AllowedCipherSuites(AllowedCipherSuites),
			_UserCertificateValidationCallback(UserCertificateValidationCallback), _UserCertificateSelectionCallback(UserCertificateSelectionCallback)
		{ }
		
		inline constexpr TlsClientAuthenticationOptions(const TlsClientAuthenticationOptions& Source)
			: _AllowRenegotiation(Source._AllowRenegotiation), _AllowedCipherSuites(Source._AllowedCipherSuites),
			_UserCertificateValidationCallback(Source._UserCertificateValidationCallback), _UserCertificateSelectionCallback(Source._UserCertificateSelectionCallback)
		{ }

		constexpr TlsClientAuthenticationOptions(TlsClientAuthenticationOptions&& Right) noexcept = delete;

		constexpr ~TlsClientAuthenticationOptions() = default;
	public:
		inline constexpr TlsClientAuthenticationOptions& operator=(const TlsClientAuthenticationOptions& Source)
		{
			if (this != &Source)
			{
				_AllowRenegotiation = Source._AllowRenegotiation;
				_AllowedCipherSuites = Source._AllowedCipherSuites;
				_UserCertificateValidationCallback = Source._UserCertificateValidationCallback;
				_UserCertificateSelectionCallback = Source._UserCertificateSelectionCallback;
			}
			return *this;
		}

		constexpr TlsClientAuthenticationOptions& operator=(TlsClientAuthenticationOptions&& Right) noexcept = delete;
	public:
		inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::Security::TlsCipherSuite>& GetAllowedCipherSuites() const
		{
			return _AllowedCipherSuites;
		}

		inline constexpr const Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&,
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Template::Net::Security::TlsPolicyErrors>& 
			GetUserCertificateValidationCallback() const
		{
			throw 1;
		}
		
		inline constexpr const Elysium::Core::Template::Container::Delegate<const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&, const void*,
			const Elysium::Core::Template::Text::StringView<char8_t>,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>&, 
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>&>&
			GetUserCertificateSelectionCallback() const
		{
			throw 1;
		}
	private:
		inline static const bool ValidateServerCertificate(const void* Sender, const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& Certificate,
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Chain& Chain, Elysium::Core::Template::Net::Security::TlsPolicyErrors PolicyErrors)
		{
			return false;
		}

		inline static constexpr const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& SelectLocalCertificate(const void* Sender,
			const Elysium::Core::Template::Text::StringView<char8_t> TargetHost,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>& LocalCertificates,
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate& RemoteCertificate,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>& AcceptableIssuers)
		{
			return LocalCertificates[0];
		}
	private:
		bool _AllowRenegotiation;
		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Net::Security::TlsCipherSuite> _AllowedCipherSuites;

		Elysium::Core::Template::Container::Delegate<const bool, const void*, const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&, 
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Chain&, 
			const Elysium::Core::Template::Net::Security::TlsPolicyErrors> _UserCertificateValidationCallback;

		Elysium::Core::Template::Container::Delegate<const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&, const void*,
			const Elysium::Core::Template::Text::StringView<char8_t>,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>&,
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate&,
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Text::String<char8_t>>&> _UserCertificateSelectionCallback;

		//_ClientCertificates;
		//_EnabledTlsProtocols;
	};
}
#endif
