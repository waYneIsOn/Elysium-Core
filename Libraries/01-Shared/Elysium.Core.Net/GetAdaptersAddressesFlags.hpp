/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_GETADAPTERSADDRESSESFLAGS
#define ELYSIUM_CORE_NET_NETWORKINFORMATION_GETADAPTERSADDRESSESFLAGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::NetworkInformation
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class GetAdaptersAddressesFlags : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
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

	inline GetAdaptersAddressesFlags operator|(GetAdaptersAddressesFlags Left, GetAdaptersAddressesFlags Right)
	{
		return static_cast<GetAdaptersAddressesFlags>(static_cast<Elysium::Core::uint16_t>(Left) | static_cast<Elysium::Core::uint16_t>(Right));
	}
	inline GetAdaptersAddressesFlags operator&(GetAdaptersAddressesFlags Left, GetAdaptersAddressesFlags Right)
	{
		return static_cast<GetAdaptersAddressesFlags>(static_cast<Elysium::Core::uint16_t>(Left) & static_cast<Elysium::Core::uint16_t>(Right));
	}
}
#endif
