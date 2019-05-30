/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE
#define ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				enum class ProtocolType : int
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
		}
	}
}
#endif
