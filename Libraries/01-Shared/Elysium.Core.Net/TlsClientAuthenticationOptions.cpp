#include "TlsClientAuthenticationOptions.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Net::Security::TlsClientAuthenticationOptions::TlsClientAuthenticationOptions(const bool AllowRenegotiation, const Collections::Template::Array<TlsCipherSuite>& AllowedCipherSuites, const RemoteCertificateValidationCallback* UserCertificateValidationCallback, const LocalCertificateSelectionCallback* UserCertificateSelectionCallback)
	: _AllowRenegotiation(AllowRenegotiation), _AllowedCipherSuites(AllowedCipherSuites)
{ }
Elysium::Core::Net::Security::TlsClientAuthenticationOptions::TlsClientAuthenticationOptions(const TlsClientAuthenticationOptions & Source)
	: _AllowRenegotiation(Source._AllowRenegotiation), _AllowedCipherSuites(Source._AllowedCipherSuites)
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
