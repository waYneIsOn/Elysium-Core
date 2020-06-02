/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_CIPHERALGORITHMTYPE
#define ELYSIUM_CORE_SECURITY_AUTHENTICATION_CIPHERALGORITHMTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class CipherAlgorithmType : uint16_t
#elif defined(__ANDROID__)
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
