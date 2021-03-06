#include "TlsClientAuthenticationOptions.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Net::Security::TlsClientAuthenticationOptions::TlsClientAuthenticationOptions(const bool AllowRenegotiation, const Collections::Template::Array<TlsCipherSuite>& AllowedCipherSuites)
	: _AllowRenegotiation(AllowRenegotiation), _AllowedCipherSuites(AllowedCipherSuites), 
	_UserCertificateValidationCallback(Elysium::Core::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::TlsPolicyErrors>::CreateDelegate<&Elysium::Core::Net::Security::TlsClientAuthenticationOptions::ValidateServerCertificate>()), 
	_UserCertificateSelectionCallback(Elysium::Core::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Collections::Template::Array<Elysium::Core::String>&>::CreateDelegate<&Elysium::Core::Net::Security::TlsClientAuthenticationOptions::SelectLocalCertificate>())
{ }
Elysium::Core::Net::Security::TlsClientAuthenticationOptions::TlsClientAuthenticationOptions(const bool AllowRenegotiation, const Collections::Template::Array<TlsCipherSuite>& AllowedCipherSuites,
	Elysium::Core::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::TlsPolicyErrors> & UserCertificateValidationCallback,
	Elysium::Core::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Collections::Template::Array<Elysium::Core::String>&> & UserCertificateSelectionCallback)
	: _AllowRenegotiation(AllowRenegotiation), _AllowedCipherSuites(AllowedCipherSuites), _UserCertificateValidationCallback(UserCertificateValidationCallback), _UserCertificateSelectionCallback(UserCertificateSelectionCallback)
{ }
Elysium::Core::Net::Security::TlsClientAuthenticationOptions::TlsClientAuthenticationOptions(const TlsClientAuthenticationOptions & Source)
	: _AllowRenegotiation(Source._AllowRenegotiation), _AllowedCipherSuites(Source._AllowedCipherSuites), _UserCertificateValidationCallback(Source._UserCertificateValidationCallback), _UserCertificateSelectionCallback(Source._UserCertificateSelectionCallback)
{ }
Elysium::Core::Net::Security::TlsClientAuthenticationOptions::~TlsClientAuthenticationOptions()
{ }

Elysium::Core::Net::Security::TlsClientAuthenticationOptions & Elysium::Core::Net::Security::TlsClientAuthenticationOptions::operator=(const TlsClientAuthenticationOptions & Source)
{
	if (this != &Source)
	{
		_AllowRenegotiation = Source._AllowRenegotiation;
		_AllowedCipherSuites = Source._AllowedCipherSuites;
	}
	return *this;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::Net::Security::TlsCipherSuite>& Elysium::Core::Net::Security::TlsClientAuthenticationOptions::GetAllowedCipherSuites() const
{
	return _AllowedCipherSuites;
}
const Elysium::Core::Delegate<const bool, const void*, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain&, const Elysium::Core::Net::Security::TlsPolicyErrors> & Elysium::Core::Net::Security::TlsClientAuthenticationOptions::GetUserCertificateValidationCallback() const
{
	return _UserCertificateValidationCallback;
}
const Elysium::Core::Delegate<const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const void*, const Elysium::Core::String&, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection&, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate&, const Elysium::Core::Collections::Template::Array<Elysium::Core::String>&> & Elysium::Core::Net::Security::TlsClientAuthenticationOptions::GetUserCertificateSelectionCallback() const
{
	return _UserCertificateSelectionCallback;
}

const bool Elysium::Core::Net::Security::TlsClientAuthenticationOptions::ValidateServerCertificate(const void * Sender, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Certificate, const Elysium::Core::Security::Cryptography::X509Certificates::X509Chain & Chain, const TlsPolicyErrors PolicyErrors)
{
	return false;
}
const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Elysium::Core::Net::Security::TlsClientAuthenticationOptions::SelectLocalCertificate(const void * Sender, const Elysium::Core::String & TargetHost, const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection & LocalCertificates, const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & RemoteCertificate, const Collections::Template::Array<Elysium::Core::String>& AcceptableIssuers)
{
	return LocalCertificates[0];
}
