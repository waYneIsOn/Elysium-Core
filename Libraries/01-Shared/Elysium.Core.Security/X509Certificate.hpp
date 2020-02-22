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

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	class ELYSIUM_CORE_API X509Certificate final
	{
	public:
		X509Certificate(const Collections::Template::Array<byte>& RawData, const String& Password = u"", const X509KeyStorageFlags Flags = X509KeyStorageFlags::All);
		X509Certificate(const String& FileName, const String& Password = u"", const X509KeyStorageFlags Flags = X509KeyStorageFlags::All);
		X509Certificate(const X509Certificate& Source);
		X509Certificate(X509Certificate&& Right) noexcept;
		~X509Certificate();

		X509Certificate& operator=(const X509Certificate& Source);
		X509Certificate& operator=(X509Certificate&& Right) noexcept;
	private:
		static const String _Format;

		Collections::Template::Array<byte> _RawData;

		void LoadCertificateFromBlob(const Collections::Template::Array<byte>& RawData, const String& Password, const X509KeyStorageFlags Flags);
		void LoadCertificateFromFile(const String& FileName, const String& Password, const X509KeyStorageFlags Flags);
	};
}
#endif
