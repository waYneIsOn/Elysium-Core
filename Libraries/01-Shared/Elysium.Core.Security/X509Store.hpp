/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORELOCATION
#include "StoreLocation.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORENAME
#include "StoreName.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_OPENFLAGS
#include "OpenFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#include "X509CertificateCollection.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_API X509Store final
	{
	public:
		X509Store(const StoreName StoreName, const StoreLocation StoreLocation);
		X509Store(const X509Store& Source) = delete;
		X509Store(X509Store&& Right) noexcept = delete;
		~X509Store();

		X509Store& operator=(const X509Store& Source) = delete;
		X509Store& operator=(X509Store&& Right) noexcept = delete;

		const bool GetIsOpen() const;
		const X509CertificateCollection& GetCertificates() const;

		void Open(const OpenFlags OpenFlags);
	private:
		X509CertificateCollection _CertificateCollection = { };
		const StoreName _StoreName;
		const StoreLocation _StoreLocation;

		ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATESTOREPOINTER _NativeCertificateStore = nullptr;
	};
}
#endif
