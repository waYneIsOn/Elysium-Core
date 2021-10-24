/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_EXCHANGEALGORITHMTYPE
#define ELYSIUM_CORE_SECURITY_AUTHENTICATION_EXCHANGEALGORITHMTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ExchangeAlgorithmType : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class ExchangeAlgorithmType
#else
#error "undefined os"
#endif
	{
		None = 0,

		RsaSign = 9216,

		RsaKeyX = 41984,

		DiffieHellman = 43522
	};
}
#endif
