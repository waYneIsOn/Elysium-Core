/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "../Elysium.Core.Security/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_SYSTEM
#include "../Elysium.Core.Security/System.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE
#include "X509ContentType.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509KEYSTORAGEFLAGS
#include "X509KeyStorageFlags.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_SECURITY_API X509Certificate final
	{
		friend class X509Chain;
		friend class Elysium::Core::Template::Container::Vector<X509Certificate>;
	private:
		X509Certificate();
	public:
		X509Certificate(ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER CertificateContext);

		X509Certificate(const X509Certificate& Source);

		X509Certificate(X509Certificate&& Right) noexcept;

		~X509Certificate();
	public:
		X509Certificate& operator=(const X509Certificate& Source);

		X509Certificate& operator=(X509Certificate&& Right) noexcept;
	public:
		const bool operator==(const X509Certificate& Other) const;
	public:
		const Elysium::Core::Utf8String GetIssuer() const;

		const Elysium::Core::Utf8String GetSubject() const;

		const Elysium::Core::Container::VectorOfByte GetRawCertData() const;
	public:
		Elysium::Core::Container::VectorOfByte Export(const X509ContentType ContentType, const char8_t* Password);

		// @ToDo: export directly to stream
	public:
		static X509Certificate LoadFromBlob(const Elysium::Core::Container::VectorOfByte& RawData, const Elysium::Core::Utf8String& Password = u8"", const X509KeyStorageFlags Flags = X509KeyStorageFlags::All);
		
		static X509Certificate LoadFromBlob(const byte* RawData, const uint32_t DataLength, const Elysium::Core::Utf8String& Password = u8"", const X509KeyStorageFlags Flags = X509KeyStorageFlags::All);
		
		static X509Certificate LoadFromFile(const char8_t* FileName, const Elysium::Core::Utf8String& Password = u8"", const X509KeyStorageFlags Flags = X509KeyStorageFlags::All);
	private:
		ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_CERTIFICATECONTEXTPOINTER _CertificateContext = nullptr;
	};
}
#endif
