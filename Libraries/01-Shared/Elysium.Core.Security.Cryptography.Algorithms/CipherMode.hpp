/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CIPHERMODE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CIPHERMODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class CipherMode 
		: Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class CipherMode
#else
#error "undefined os"
#endif
	{
		CBC = 1,

		ECB = 2,

		OFB = 3,

		CFB = 4,

		CTS = 5
	};
}
#endif
