#include "X509Store.hpp"

Elysium::Core::Security::Cryptography::X509Certificates::X509Store::X509Store(const StoreName StoreName, const StoreLocation StoreLocation)
	: _StoreName(StoreName), _StoreLocation(StoreLocation)
{
}
Elysium::Core::Security::Cryptography::X509Certificates::X509Store::~X509Store()
{
	if (_NativeCertificateStore != nullptr)
	{
		CertCloseStore(_NativeCertificateStore, 0);
	}
}

const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection & Elysium::Core::Security::Cryptography::X509Certificates::X509Store::GetCerificateCollection() const
{
	return _CertificateCollection;
}

void Elysium::Core::Security::Cryptography::X509Certificates::X509Store::Open(const OpenFlags OpenFlags)
{
	if (_NativeCertificateStore != nullptr)
	{
		return;
	}
	_NativeCertificateStore = CertOpenSystemStore(0, L"MY");
	if (_NativeCertificateStore == nullptr)
	{
		// ToDo: throw specific exception
		throw 1;
	}
}
