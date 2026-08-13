/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_IPPROTECTIONLEVEL
#define ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_IPPROTECTIONLEVEL

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
	enum class IPProtectionLevel
		: Elysium::Core::Template::System::int8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
