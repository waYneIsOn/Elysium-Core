#include "X509Store.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Security::Cryptography::X509Certificates::X509Store::X509Store(const StoreName StoreName, const StoreLocation StoreLocation)
	: _StoreName(StoreName), _StoreLocation(StoreLocation)
{
}
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

void Elysium::Core::Security::Cryptography::X509Certificates::X509Store::Open(const OpenFlags OpenFlags)
{
	if (_NativeCertificateStore != nullptr)
	{
		return;
	}

	int StoreLocation = 0;
	switch (_StoreLocation)
	{
	case StoreLocation::CurrentUser:
		StoreLocation = CERT_SYSTEM_STORE_CURRENT_USER;
		break;
	case StoreLocation::LocalMachine:
		StoreLocation = CERT_SYSTEM_STORE_LOCAL_MACHINE;
		break;
	default:
		throw NotImplementedException(u"Unhandled StoreLocation");
	}

	WideString StoreName;
	switch (_StoreName)
	{
	case StoreName::AddressBook:
		// ToDo
		throw NotImplementedException(u"Unhandled StoreName AddressBook");
		break;
	case StoreName::AuthRoot:
		// ToDo
		throw NotImplementedException(u"Unhandled StoreName AuthRoot");
		break;
	case StoreName::CertificateAuthority:
		// ToDo
		throw NotImplementedException(u"Unhandled StoreName CertificateAuthority");
		break;
	case StoreName::Disallowed:
		// ToDo
		throw NotImplementedException(u"Unhandled StoreName Disallowed");
		break;
	case StoreName::My:
		StoreName = L"MY";
		break;
	case StoreName::Root:
		StoreName = L"ROOT";
		break;
	case StoreName::TrustedPeople:
		// ToDo
		throw NotImplementedException(u"Unhandled StoreName TrustedPeople");
		break;
	case StoreName::TrustedPublisher:
		// ToDo
		throw NotImplementedException(u"Unhandled StoreName TrustedPublisher");
		break;
	default:
		throw NotImplementedException(u"Unhandled StoreName");
	}

	if ((_NativeCertificateStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, NULL, StoreLocation, &StoreName[0])) == nullptr)
	{
		// ToDo: throw specific exception
		throw GetLastError();
	}
	else
	{
		ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER CertificateContextPointer = nullptr;
		while (CertificateContextPointer = CertEnumCertificatesInStore(_NativeCertificateStore, CertificateContextPointer))
		{
			_CertificateCollection.Add(X509Certificate(CertificateContextPointer));
		}
		CertFreeCertificateContext(CertificateContextPointer);
	}
}
