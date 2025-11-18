/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_PRINCIPAL_TOKENIMPERSONATIONLEVEL
#define ELYSIUM_CORE_SECURITY_PRINCIPAL_TOKENIMPERSONATIONLEVEL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/OperatingSystem.hpp"
#endif

namespace Elysium::Core::Security::Principal
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class TokenImpersonationLevel
		: Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TokenImpersonationLevel
#else
#error "undefined os"
#endif
	{
		None = 0,

		Anonymous = 1,

		Identification = 2,

		Impersonation = 3,

		Delegation = 4
	};
}
#endif
