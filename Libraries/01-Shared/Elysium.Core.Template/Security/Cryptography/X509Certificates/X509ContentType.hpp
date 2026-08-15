/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509CONTENTTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::X509Certificates
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class X509ContentType
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
