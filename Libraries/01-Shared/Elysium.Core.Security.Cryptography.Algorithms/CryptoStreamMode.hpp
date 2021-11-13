/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOSTREAMMODE
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CRYPTOSTREAMMODE

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
	enum class CryptoStreamMode : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class CryptoStreamMode
#else
#error "undefined os"
#endif
	{
		Read = 0,

		Write = 1
	};
}
#endif
