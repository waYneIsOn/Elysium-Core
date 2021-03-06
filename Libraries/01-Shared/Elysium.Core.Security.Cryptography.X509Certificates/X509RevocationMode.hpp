/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONMODE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509REVOCATIONMODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class X509RevocationMode : uint32_t
#elif defined(__ANDROID__)
	enum class X509RevocationMode
#else
#error "undefined os"
#endif
	{
		NoCheck = 0,
		Online = 1,
		Offline = 2,
	};
}
#endif
