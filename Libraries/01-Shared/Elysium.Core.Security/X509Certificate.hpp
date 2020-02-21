/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CERTIFICATE

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
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

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_API X509Certificate final
	{
	public:
		X509Certificate(const String& FileName, const String& Password = u"", const X509KeyStorageFlags Flags = KeyStorageFlagsAll);
		X509Certificate(const X509Certificate& Source) = delete;
		X509Certificate(X509Certificate&& Right) noexcept = delete;
		~X509Certificate();

		X509Certificate& operator=(const X509Certificate& Source) = delete;
		X509Certificate& operator=(X509Certificate&& Right) noexcept = delete;
	private:
		static const String _Format;
		static const X509KeyStorageFlags KeyStorageFlagsAll;

		String _Subject;
		String _IssuerName;
		//Collections::Template::Array<byte> _SerialNumber;
		//Collections::Template::Array<byte> _PublicKeyParameters;
		//Collections::Template::Array<byte> _PublicKeyValue;
		String _PublicKeyOid;
		//Collections::Template::Array<byte> _RawData;
		//Collections::Template::Array<byte> _ThumbPrint;

		void LoadCertificateFromBlob(const Collections::Template::Array<byte>& RawData, const String& Password, const X509KeyStorageFlags Flags);
		void LoadCertificateFromFile(const String& FileName, const String& Password, const X509KeyStorageFlags Flags);
	};
}
#endif
