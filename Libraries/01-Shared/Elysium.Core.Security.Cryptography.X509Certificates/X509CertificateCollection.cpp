#include "X509CertificateCollection.hpp"

Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::X509CertificateCollection()
	: _Certificates()
{ }
Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::~X509CertificateCollection()
{ }

const Elysium::Core::Security::Cryptography::X509Certificates::X509Certificate & Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::operator[](Elysium::Core::size Index) const
{
	return _Certificates[Index];
}

const Elysium::Core::size Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::GetCount() const
{
	return _Certificates.GetCount();
}

void Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::Add(X509Certificate && Item)
{
	_Certificates.Add(Elysium::Core::Template::Functional::Move(Item));
}
void Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection::Clear()
{
	_Certificates.Clear();
}

