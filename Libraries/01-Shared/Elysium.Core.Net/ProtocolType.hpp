/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE
#define ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ProtocolType : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class ProtocolType
#else
#error "undefined os"
#endif
	{
		//Unknown = -1,

		Unspecified = 0,
		IP = 0,
		IPv6HopByHopOptions = 0,
		Icmp = 1,
		Igmp = 2,
		Ggp = 3,
		IPv4 = 4,
		Tcp = 6,
		Udp = 17,
		Pup = 12,
		Idp = 22,
		IPv6 = 41,
		IPv6RoutingHeader = 43,
		IPv6FragmentHeader = 44,
		IPSecEncapsulatingSecurityPayload = 50,
		IPSecAuthenticationHeader = 51,
		IcmpV6 = 58,
		IPv6NoNextHeader = 59,
		IPv6DestinationOptions = 60,
		ND = 77,
		Raw = 255,
		Ipx = 1000,
		Spx = 1256,
		SpxII = 1257
	};
}
#endif
