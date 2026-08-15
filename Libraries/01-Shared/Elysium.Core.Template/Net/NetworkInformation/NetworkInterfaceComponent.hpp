/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_NETWORKINFORMATION_NETWORKINTERFACECOMPONENT
#define ELYSIUM_CORE_TEMPLATE_NET_NETWORKINFORMATION_NETWORKINTERFACECOMPONENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Net::NetworkInformation
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class NetworkInterfaceComponent
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class NetworkInterfaceComponent
#else
#error "undefined os"
#endif
	{
		IPv4 = 0,

		IPv6 = 1,
	};
}
#endif
#pragma once
