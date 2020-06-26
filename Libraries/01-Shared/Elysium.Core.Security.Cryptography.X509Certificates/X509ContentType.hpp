/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class X509ContentType : uint32_t
#elif defined(__ANDROID__)
	enum class X509ContentType
#else
#error "undefined os"
#endif
	{
		Unknown = 0x00,
		Cert = 0x01,
		SerializedCert = 0x02,
		Pfx = 0x03,
		Pkcs12 = Pfx,
		SerializedStore = 0x04,
		Pkcs7 = 0x05,
		Authenticode = 0x06
	};
}
#endif
