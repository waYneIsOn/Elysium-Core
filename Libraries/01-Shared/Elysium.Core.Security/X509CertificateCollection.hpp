/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_API X509CertificateCollection final
	{
	public:
		X509CertificateCollection();
		X509CertificateCollection(const X509CertificateCollection& Source) = delete;
		X509CertificateCollection(X509CertificateCollection&& Right) noexcept = delete;
		~X509CertificateCollection();

		X509CertificateCollection& operator=(const X509CertificateCollection& Source) = delete;
		X509CertificateCollection& operator=(X509CertificateCollection&& Right) noexcept = delete;
	};
}
#endif
