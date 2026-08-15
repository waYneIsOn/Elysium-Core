/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_NETWORKINFORMATION_OPERATIONALSTATUS
#define ELYSIUM_CORE_TEMPLATE_NET_NETWORKINFORMATION_OPERATIONALSTATUS

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
	enum class OperationalStatus
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class OperationalStatus
#else
#error "undefined os"
#endif
	{
		Up = 1,

		Down = 2,

		Testing = 3,

		Unknown = 4,

		Dormant = 5,

		NotPresent = 6,

		LowerLayerDown = 7
	};
}
#endif
#pragma once
