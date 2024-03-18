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

		/// <summary>
		/// 
		/// </summary>
		Unspecified = 0,

		/// <summary>
		/// 
		/// </summary>
		IP = 0,

		/// <summary>
		/// 
		/// </summary>
		IPv6HopByHopOptions = 0,

		/// <summary>
		/// 
		/// </summary>
		Icmp = 1,

		/// <summary>
		/// 
		/// </summary>
		Igmp = 2,

		/// <summary>
		/// 
		/// </summary>
		Ggp = 3,

		/// <summary>
		/// 
		/// </summary>
		IPv4 = 4,

		/// <summary>
		/// 
		/// </summary>
		Tcp = 6,

		/// <summary>
		/// 
		/// </summary>
		Udp = 17,

		/// <summary>
		/// 
		/// </summary>
		Pup = 12,

		/// <summary>
		/// 
		/// </summary>
		Idp = 22,

		/// <summary>
		/// 
		/// </summary>
		IPv6 = 41,

		/// <summary>
		/// 
		/// </summary>
		IPv6RoutingHeader = 43,

		/// <summary>
		/// 
		/// </summary>
		IPv6FragmentHeader = 44,

		/// <summary>
		/// 
		/// </summary>
		IPSecEncapsulatingSecurityPayload = 50,

		/// <summary>
		/// 
		/// </summary>
		IPSecAuthenticationHeader = 51,

		/// <summary>
		/// 
		/// </summary>
		IcmpV6 = 58,

		/// <summary>
		/// 
		/// </summary>
		IPv6NoNextHeader = 59,

		/// <summary>
		/// 
		/// </summary>
		IPv6DestinationOptions = 60,

		/// <summary>
		/// 
		/// </summary>
		ND = 77,

		/// <summary>
		/// 
		/// </summary>
		Raw = 255,

		/// <summary>
		/// 
		/// </summary>
		Ipx = 1000,

		/// <summary>
		/// 
		/// </summary>
		Spx = 1256,

		/// <summary>
		/// 
		/// </summary>
		SpxII = 1257
	};
}
#endif
