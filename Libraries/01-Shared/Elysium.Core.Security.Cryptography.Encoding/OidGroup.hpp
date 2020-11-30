/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDGROUP
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_OIDGROUP

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class OidGroup : uint32_t
#elif defined(__ANDROID__)
	enum class OidGroup
#else
#error "undefined os"
#endif
	{
		All = 0,
		HashAlgorithm = 1,
		EncryptionAlgorithm = 2,
		PublicKeyAlgorithm = 3,
		SignatureAlgorithm = 4,
		Attribute = 5,
		ExtensionOrAttribute = 6,
		EnhancedKeyUsage = 7,
		Policy = 8,
		Template = 9,
		KeyDerivationFunction = 10
	};
}
#endif
