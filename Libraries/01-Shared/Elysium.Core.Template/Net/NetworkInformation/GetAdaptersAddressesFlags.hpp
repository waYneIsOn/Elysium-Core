/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_NETWORKINFORMATION_GETADAPTERSADDRESSESFLAGS
#define ELYSIUM_CORE_TEMPLATE_NET_NETWORKINFORMATION_GETADAPTERSADDRESSESFLAGS

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
	enum class GetAdaptersAddressesFlags
		: Elysium::Core::Template::System::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class GetAdaptersAddressesFlags
#else
#error "undefined os"
#endif
	{
		SkipUnicast = 0x0001,

		SkipAnycast = 0x0002,

		SkipMulticast = 0x0004,

		SkipDnsServer = 0x0008,

		IncludePrefix = 0x0010,

		SkipFriendlyName = 0x0020,

		IncludeWins = 0x0040,

		IncludeGateways = 0x0080,

		IncludeAllInterfaces = 0x0100,

		IncludeAllCompartments = 0x0200,

		IncludeTunnelBindingOrder = 0x0400,
	};

	inline GetAdaptersAddressesFlags operator|(const GetAdaptersAddressesFlags Left, const GetAdaptersAddressesFlags Right)
	{
		return static_cast<GetAdaptersAddressesFlags>(static_cast<Elysium::Core::Template::System::uint16_t>(Left) | static_cast<Elysium::Core::Template::System::uint16_t>(Right));
	}

	inline GetAdaptersAddressesFlags operator&(const GetAdaptersAddressesFlags Left, const GetAdaptersAddressesFlags Right)
	{
		return static_cast<GetAdaptersAddressesFlags>(static_cast<Elysium::Core::Template::System::uint16_t>(Left) & static_cast<Elysium::Core::Template::System::uint16_t>(Right));
	}
}
#endif
#pragma once
