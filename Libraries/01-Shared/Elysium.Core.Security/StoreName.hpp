/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORENAME
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORENAME

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class StoreName : uint32_t
#elif defined(__ANDROID__)
	enum class StoreName
#else
#error "undefined os"
#endif
	{
		AddressBook = 1,
		AuthRoot = 2,
		CertificateAuthority = 3,
		Disallowed = 4,
		My = 5,
		Root = 6,
		TrustedPeople = 7,
		TrustedPublisher = 8
	};
}
#endif
