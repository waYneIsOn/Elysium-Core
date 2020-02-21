/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509STORE

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

#ifndef __WINCRYPT_H__
#ifndef _WINDOWS_
#include <windows.h>
#endif

#include <wincrypt.h>
#pragma comment(lib, "Crypt32.Lib")
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#include "X509CertificateCollection.hpp"
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

		const X509CertificateCollection& GetCerificateCollection() const;

		void Open(const OpenFlags OpenFlags);
	private:
		X509CertificateCollection _CertificateCollection = { };
		const StoreName _StoreName;
		const StoreLocation _StoreLocation;

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		HCERTSTORE _NativeCertificateStore = nullptr;
#elif defined(__ANDROID__)

#else

#endif
	};
}
#endif
