/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_CIPHERALGORITHMTYPE
#define ELYSIUM_CORE_SECURITY_AUTHENTICATION_CIPHERALGORITHMTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class CipherAlgorithmType : Elysium::Core::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class CipherAlgorithmType
#else
#error "undefined os"
#endif
	{
		None = 0,

		Null = 24576,

		Des = 26113,
		Rc2 = 26114,
		TripleDes = 26115,

		Rc4 = 26625,
		Aes128 = 26126,
		Aes192 = 26127,
		Aes256 = 26128,
		Aes = 26129,
	};
}
#endif
