/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE
#define ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class ProtocolType : uint32_t
#elif defined(__ANDROID__)
	enum class ProtocolType
#else
#error "undefined os"
#endif
	{
		Ggp,
		Icmp,
		IcmpV6,
		Idp,
		Igmp,
		IP,
		IPSecAuthenticationHeader,
		IPSecEncapsulatingSecurityPayload,
		IPv4,
		IPv6,
		IPv6DestinationOptions,
		IPv6FragmentHeader,
		IPv6HopByHopOptions,
		IPv6NoNextHeader,
		IPv6RoutingHeader,
		Ipx,
		ND,
		Pup,
		Raw,
		Spx,
		SpxII,
		Tcp,
		Udp,
		Unknown,
		Unspecified,
	};
}
#endif
