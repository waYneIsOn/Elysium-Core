#include "X509Store.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Security::Cryptography::X509Certificates::X509Store::X509Store(const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName StoreName, const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreLocation StoreLocation)
	: _StoreName(StoreName), _StoreLocation(StoreLocation)
{ }

Elysium::Core::Security::Cryptography::X509Certificates::X509Store::~X509Store()
{
	if (_NativeCertificateStore != nullptr)
	{
		CertCloseStore(_NativeCertificateStore, CERT_CLOSE_STORE_CHECK_FLAG);	// CERT_CLOSE_STORE_FORCE_FLAG
		_NativeCertificateStore = nullptr;
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

void Elysium::Core::Security::Cryptography::X509Certificates::X509Store::Open(const Elysium::Core::Template::Security::Cryptography::X509Certificates::OpenFlags OpenFlags)
{
	if (_NativeCertificateStore != nullptr)
	{
		return;
	}

	int StoreLocation = 0;
	switch (_StoreLocation)
	{
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreLocation::CurrentUser:
		StoreLocation = CERT_SYSTEM_STORE_CURRENT_USER;
		break;
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreLocation::LocalMachine:
		StoreLocation = CERT_SYSTEM_STORE_LOCAL_MACHINE;
		break;
	default:
		throw NotImplementedException(u8"Unhandled StoreLocation");
	}

	const wchar_t* StoreName;
	switch (_StoreName)
	{
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName::AddressBook:
		StoreName = L"ADDRESSBOOK";
		break;
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName::AuthRoot:
		StoreName = L"AUTHROOT";
		break;
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName::CertificateAuthority:
		StoreName = L"CERTIFICATEAUTHORITY";
		break;
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName::Disallowed:
		StoreName = L"DISALLOWED";
		break;
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName::My:
		StoreName = L"MY";
		break;
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName::Root:
		StoreName = L"ROOT";
		break;
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName::TrustedPeople:
		StoreName = L"TRUSTEDPEOPLE";
		break;
	case Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName::TrustedPublisher:
		StoreName = L"TRUSTEDPUBLISHER";
		break;
	default:
		throw NotImplementedException(u8"Unhandled StoreName");
	}

	if ((_NativeCertificateStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, StoreLocation, &StoreName[0])) == nullptr)
	{
		// ToDo: throw specific exception
		throw GetLastError();
	}
	else
	{
		PCCERT_CONTEXT CertificateContextPointer = nullptr;
		while (CertificateContextPointer = CertEnumCertificatesInStore(_NativeCertificateStore, CertificateContextPointer))
		{
			_CertificateCollection.Add(X509Certificate(CertificateContextPointer));
		}
		CertFreeCertificateContext(CertificateContextPointer);
	}
}
