/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_AUTHENTICATION_EXCHANGEALGORITHMTYPE
#define ELYSIUM_CORE_TEMPLATE_SECURITY_AUTHENTICATION_EXCHANGEALGORITHMTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Authentication
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class ExchangeAlgorithmType
		: Elysium::Core::Template::System::uint16_t
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
