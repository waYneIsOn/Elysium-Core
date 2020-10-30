/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_OPERATIONALSTATUS
#define ELYSIUM_CORE_NET_NETWORKINFORMATION_OPERATIONALSTATUS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::NetworkInformation
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class OperationalStatus : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
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
