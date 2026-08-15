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

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE
#include "../Elysium.Core.Template/Security/Cryptography/X509Certificates/X509ContentType.hpp"
#endif

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509KEYSTORAGEFLAGS
#include "../Elysium.Core.Template/Security/Cryptography/X509Certificates/X509KeyStorageFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef __WINCRYPT_H__
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <windows.h>
	#endif

	#include <wincrypt.h>
	#pragma comment(lib, "Crypt32.Lib")
	#endif
#endif

namespace Elysium::Core::Net::Security
{
	class TlsStream;
}

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_SECURITY_API X509Certificate final
	{
		friend class X509Chain;
		friend class Elysium::Core::Template::Container::Vector<X509Certificate>;
		friend class Elysium::Core::Net::Security::TlsStream;
	private:
		X509Certificate();
	public:
#if defined ELYSIUM_CORE_OS_WINDOWS
		X509Certificate(PCCERT_CONTEXT CertificateContext, HCRYPTPROV_OR_NCRYPT_KEY_HANDLE PrivateKeyHandle = 0, 
			const bool OwnsPrivateKeyHandle = false, const DWORD KeySpecifications = -1);
#endif
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
		Elysium::Core::Container::VectorOfByte Export(const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509ContentType ContentType, const char8_t* Password);

		// @ToDo: export directly to stream
	public:
		static X509Certificate LoadFromBlob(const Elysium::Core::Container::VectorOfByte& RawData, const Elysium::Core::Utf8String& Password = u8"", 
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags Flags = Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags::All);
		
		static X509Certificate LoadFromBlob(const byte* RawData, const uint32_t DataLength, const Elysium::Core::Utf8String& Password = u8"", 
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags Flags = Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags::All);
		
		static X509Certificate LoadFromFile(const char8_t* FileName, const Elysium::Core::Utf8String& Password = u8"", 
			const Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags Flags = Elysium::Core::Template::Security::Cryptography::X509Certificates::X509KeyStorageFlags::All);
#if defined ELYSIUM_CORE_OS_WINDOWS
	private:
		HCRYPTPROV_OR_NCRYPT_KEY_HANDLE CopyPrivateKeyHandle(const X509Certificate& Source);
	private:
		PCCERT_CONTEXT _CertificateContext;

		bool _OwnsPrivateKeyHandle;
		HCRYPTPROV_OR_NCRYPT_KEY_HANDLE _PrivateKeyHandle;
		DWORD _KeySpecifications;
#endif
	};
}
#endif
