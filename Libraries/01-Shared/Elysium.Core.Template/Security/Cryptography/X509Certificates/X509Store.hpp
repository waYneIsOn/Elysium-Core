/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_OPENFLAGS
#include "OpenFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORELOCATION
#include "StoreLocation.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORENAME
#include "StoreName.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef __WINCRYPT_H__
#include <wincrypt.h>
#endif

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Crypt32.Lib")
#pragma comment(lib, "Ncrypt.Lib")
#endif

namespace Elysium::Core::Template::Security::Cryptography::X509Certificates
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	class X509Store
	{
	public:
		constexpr X509Store() = delete;

		inline constexpr X509Store(const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName StoreName,
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreLocation StoreLocation)
			: _StoreName(StoreName), _StoreLocation(StoreLocation), _CertificateCollection{}, _NativeCertificateStore{}
		{ }

		constexpr X509Store(const X509Store& Source) = delete;

		constexpr X509Store(X509Store&& Right) noexcept = delete;

		inline constexpr ~X509Store()
		{
			if (_NativeCertificateStore != nullptr)
			{
				CertCloseStore(_NativeCertificateStore, CERT_CLOSE_STORE_CHECK_FLAG);	// CERT_CLOSE_STORE_FORCE_FLAG
				_NativeCertificateStore = nullptr;
			}
		}
	public:
		constexpr X509Store& operator=(const X509Store& Source) = delete;

		constexpr X509Store& operator=(X509Store&& Right) noexcept = delete;
	public:
		inline constexpr const bool GetIsOpen() const
		{
			return _NativeCertificateStore != nullptr;
		}

		inline constexpr const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate>& GetCertificates() const
		{
			return _CertificateCollection;
		}
	public:
		inline void Open(const Elysium::Core::Template::Security::Cryptography::X509Certificates::OpenFlags OpenFlags)
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
				// @ToDo
				throw;
				//throw NotImplementedException(u8"Unhandled StoreLocation");
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
				// @ToDo
				throw;
				//throw NotImplementedException(u8"Unhandled StoreName");
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
					_CertificateCollection.PushBack(X509Certificate(CertificateContextPointer));
				}
				CertFreeCertificateContext(CertificateContextPointer);
			}
		}
	private:
		const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName _StoreName;
		const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreLocation _StoreLocation;

		Elysium::Core::Template::Container::Vector<Elysium::Core::Template::Security::Cryptography::X509Certificates::X509Certificate> _CertificateCollection;
		HCERTSTORE _NativeCertificateStore;
	};
#endif
}
#endif
