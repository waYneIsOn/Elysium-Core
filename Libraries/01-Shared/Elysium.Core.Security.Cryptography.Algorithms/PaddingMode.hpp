/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_PADDINGMODE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_PADDINGMODE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Security::Cryptography
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class PaddingMode : Elysium::Core::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class PaddingMode
#else
#error "undefined os"
#endif
	{
		None = 1,

		PKCS7 = 2,

		Zeros = 3,

		ANSIX923 = 4,

		ISO10126 = 5
	};
}
#endif
