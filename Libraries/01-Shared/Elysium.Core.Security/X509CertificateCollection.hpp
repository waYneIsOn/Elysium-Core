/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATECOLLECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#include "X509Certificate.hpp"
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

		const X509Certificate& operator[](size_t Index) const;

		const size_t GetCount() const;

		void Add(X509Certificate&& Item);
		void Clear();
	private:
		Collections::Template::List<X509Certificate> _Certificates = { };
	};
}
#endif
