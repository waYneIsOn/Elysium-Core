/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE

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
		Unknown = 0,
		Cert = 1,
		SerializedCert = 2,
		Pfx = 3,
		Pkcs12 = 3,
		SerializedStore = 4,
		Pkcs7 = 5,
		Authenticode = 6
	};
}
#endif
