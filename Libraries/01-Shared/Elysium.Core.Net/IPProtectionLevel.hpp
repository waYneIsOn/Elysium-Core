/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_IPPROTECTIONLEVEL
#define ELYSIUM_CORE_NET_SOCKETS_IPPROTECTIONLEVEL

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class IPProtectionLevel : Elysium::Core::int8_t
#elif defined(__ANDROID__)
	enum class IPProtectionLevel
#else
#error "undefined os"
#endif
	{
		Unspecified = -1,

		Unrestricted = 10,

		EdgeRestricted = 20,

		Restricted = 30
	};
}
#endif
