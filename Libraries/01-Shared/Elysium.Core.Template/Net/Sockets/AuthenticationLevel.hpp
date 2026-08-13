/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_AUTHENTICATIONLEVEL
#define ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_AUTHENTICATIONLEVEL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Net::Sockets
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class AuthenticationLevel
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class AuthenticationLevel
#else
#error "undefined os"
#endif
	{
		None = 0,

		MutualAuthRequested = 1,

		MutualAuthRequired = 2
	};
}
#endif
