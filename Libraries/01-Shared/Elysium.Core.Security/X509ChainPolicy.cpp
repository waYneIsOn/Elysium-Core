#include "X509ChainPolicy.hpp"

Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::X509ChainPolicy()
{ }
Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::~X509ChainPolicy()
{ }

const Elysium::Core::Security::Cryptography::OidCollection & Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::GetApplicationPolicy() const
{
	return _ApplicationPolicy;
}
const Elysium::Core::Security::Cryptography::OidCollection & Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::GetCertificatePolicy() const
{
	return _CertificatePolicy;
}
const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection & Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::GetExtraStore() const
{
	return _ExtraStore;
}
const Elysium::Core::Security::Cryptography::X509Certificates::X509RevocationFlag Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::GetRevocationFlag() const
{
	return _RevocationFlag;
}
const Elysium::Core::Security::Cryptography::X509Certificates::X509RevocationMode Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::GetRevocationMode() const
{
	return _RevocationMode;
}
const Elysium::Core::TimeSpan Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::GetUrlRetrievalTimeout() const
{
	return _UrlRetrievalTimeout;
}
const Elysium::Core::Security::Cryptography::X509Certificates::X509VerificationFlags Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::GetVerificationFlags() const
{
	return _VerificationFlags;
}
const Elysium::Core::DateTime Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::GetVerificationTime() const
{
	return _VerificationTime;
}

void Elysium::Core::Security::Cryptography::X509Certificates::X509ChainPolicy::Reset()
{

}
