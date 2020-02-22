#include "X509CertificateCollection.hpp"

Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::X509CertificateCollection()
{
}
Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::~X509CertificateCollection()
{
}

const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::operator[](size_t Index) const
{
	return _Certificates[Index];
}

const size_t Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::GetCount() const
{
	return _Certificates.GetCount();
}

void Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::Add(const X509Certificate & Item)
{
	_Certificates.Add(Item);
}
void Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::Clear()
{
	_Certificates.Clear();
}
