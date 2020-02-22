#include "X509Store.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
#endif

Elysium::Core::Security::Cryptography::X509Certificates::X509Store::X509Store(const StoreName StoreName, const StoreLocation StoreLocation)
	: _StoreName(StoreName), _StoreLocation(StoreLocation)
{
}
Elysium::Core::Security::Cryptography::X509Certificates::X509Store::~X509Store()
{
	_CertificateCollection.Clear();
	if (_NativeCertificateStore != nullptr)
	{
		CertCloseStore(_NativeCertificateStore, CERT_CLOSE_STORE_CHECK_FLAG);
	}
}

const bool Elysium::Core::Security::Cryptography::X509Certificates::X509Store::GetIsOpen() const
{
	return _NativeCertificateStore != nullptr;
}
const Elysium::Core::Security::Cryptography::X509Certificates::X509CertificateCollection & Elysium::Core::Security::Cryptography::X509Certificates::X509Store::GetCertificates() const
{
	return _CertificateCollection;
}

void Elysium::Core::Security::Cryptography::X509Certificates::X509Store::Open(const OpenFlags OpenFlags)
{
	if (_NativeCertificateStore != nullptr)
	{
		return;
	}
	/*
	StoreName:
		- ToWString (ie. L"MY")

	StoreLocation:
		- CERT_SYSTEM_STORE_CURRENT_USER
		- CERT_SYSTEM_STORE_LOCAL_MACHINE
		- etc.

	OpenFlags
		- ...
	*/
	if ((_NativeCertificateStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, NULL, CERT_SYSTEM_STORE_CURRENT_USER, L"ROOT")) == nullptr)
	{
		// ToDo: throw specific exception
		throw GetLastError();
	}
	else
	{
		// iterare all certificates of the opened store
		PCCERT_CONTEXT NativeCertificateContext = nullptr;
		while (NativeCertificateContext = CertEnumCertificatesInStore(_NativeCertificateStore, NativeCertificateContext))
		{
			// get the size of the certificate
			unsigned long ByteLength;
			if (CertSerializeCertificateStoreElement(NativeCertificateContext, 0, nullptr, &ByteLength))
			{
				// serialize the certificate into a byte-array
				Collections::Template::Array<byte> RawData = Collections::Template::Array<byte>(ByteLength);
				if (CertSerializeCertificateStoreElement(NativeCertificateContext, 0, &RawData[0], &ByteLength))
				{
					_CertificateCollection.Add(X509Certificate(RawData));

					int x = 234;
				}
				else
				{
					// ToDo: throw specific exception
					throw GetLastError();
				}
			}
			else
			{
				// ToDo: throw specific exception
				throw GetLastError();
			}
		}
		CertFreeCertificateContext(NativeCertificateContext);
	}
}
