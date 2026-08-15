/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OIDGROUP
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_OIDGROUP

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class OidGroup
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
