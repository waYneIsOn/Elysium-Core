/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_AUTHENTICATIONLEVEL
#define ELYSIUM_CORE_NET_SECURITY_AUTHENTICATIONLEVEL

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class AuthenticationLevel : uint32_t
#elif defined(__ANDROID__)
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
