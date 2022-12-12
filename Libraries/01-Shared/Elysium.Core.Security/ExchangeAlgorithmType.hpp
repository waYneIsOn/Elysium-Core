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
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ExchangeAlgorithmType : Elysium::Core::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
