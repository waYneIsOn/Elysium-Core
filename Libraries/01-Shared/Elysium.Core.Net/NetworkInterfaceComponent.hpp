/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACECOMPONENT
#define ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACECOMPONENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::NetworkInformation
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class NetworkInterfaceComponent : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
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
