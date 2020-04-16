/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_AUTHENTICATIONLEVEL
#define ELYSIUM_CORE_NET_SECURITY_AUTHENTICATIONLEVEL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
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
