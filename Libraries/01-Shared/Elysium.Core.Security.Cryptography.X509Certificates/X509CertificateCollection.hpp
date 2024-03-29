/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CONTAINER_VECTOROFX509CERTIFICATE
#include "VectorOfX509Certificate.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_SECURITY_API X509CertificateCollection final
	{
	public:
		X509CertificateCollection();

		X509CertificateCollection(const X509CertificateCollection& Source) = delete;

		X509CertificateCollection(X509CertificateCollection&& Right) noexcept = delete;

		~X509CertificateCollection();

		X509CertificateCollection& operator=(const X509CertificateCollection& Source) = delete;

		X509CertificateCollection& operator=(X509CertificateCollection&& Right) noexcept = delete;

		const X509Certificate& operator[](Elysium::Core::size Index) const;

		const Elysium::Core::size GetCount() const;

		void Add(X509Certificate&& Item);

		void Clear();
	private:
		Elysium::Core::Template::Container::Vector<X509Certificate> _Certificates;
	};
}
#endif
