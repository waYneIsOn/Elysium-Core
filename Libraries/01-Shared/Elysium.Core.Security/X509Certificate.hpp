/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509KEYSTORAGEFLAGS
#include "X509KeyStorageFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_SECURITY_API X509Certificate final
	{
		friend class Elysium::Core::Collections::Template::List<X509Certificate>;
		friend class X509Chain;
	public:
		X509Certificate(ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER CertificateContext);
		X509Certificate(const X509Certificate& Source);
		X509Certificate(X509Certificate&& Right) noexcept;
		~X509Certificate();

		X509Certificate& operator=(const X509Certificate& Source);
		X509Certificate& operator=(X509Certificate&& Right) noexcept;

		const String GetIssuer() const;
		const String GetSubject() const;

		const Collections::Template::Array<byte> GetRawCertData() const;


		static X509Certificate LoadFromBlob(const Collections::Template::Array<byte>& RawData, const String& Password = u"", const X509KeyStorageFlags Flags = X509KeyStorageFlags::All);
		static X509Certificate LoadFromBlob(const byte* RawData, const uint32_t DataLength, const String& Password = u"", const X509KeyStorageFlags Flags = X509KeyStorageFlags::All);
		
		static X509Certificate LoadFromFile(const String& FileName, const String& Password = u"", const X509KeyStorageFlags Flags = X509KeyStorageFlags::All);
	private:
		X509Certificate();

		ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER _CertificateContext = nullptr;
	};
}
#endif
