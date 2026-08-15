/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORELOCATION
#include "../Elysium.Core.Template/Security/Cryptography/X509Certificates/StoreLocation.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORENAME
#include "../Elysium.Core.Template/Security/Cryptography/X509Certificates/StoreName.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_OPENFLAGS
#include "../Elysium.Core.Template/Security/Cryptography/X509Certificates/OpenFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#include "X509CertificateCollection.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_SECURITY_API X509Store final
	{
	public:
		X509Store(const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName StoreName, const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreLocation StoreLocation);

		X509Store(const X509Store& Source) = delete;

		X509Store(X509Store&& Right) noexcept = delete;

		~X509Store();
	public:
		X509Store& operator=(const X509Store& Source) = delete;

		X509Store& operator=(X509Store&& Right) noexcept = delete;
	public:
		const bool GetIsOpen() const;

		const X509CertificateCollection& GetCertificates() const;
	public:
		void Open(const Elysium::Core::Template::Security::Cryptography::X509Certificates::OpenFlags OpenFlags);
	private:
		X509CertificateCollection _CertificateCollection = { };
		const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreName _StoreName;
		const Elysium::Core::Template::Security::Cryptography::X509Certificates::StoreLocation _StoreLocation;

		HCERTSTORE _NativeCertificateStore = nullptr;
	};
}
#endif
