/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#define ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class AddressFamily : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class AddressFamily
#else
#error "undefined os"
#endif
	{
		//Unknown = -1,

		Unspecified = 0,
		Unix = 1,
		InterNetwork = 2,
		ImpLink = 3,
		Pup = 4,
		Chaos = 5,
		NS = 6,
		Ipx = NS,
		Iso = 7,
		Osi = Iso,
		Ecma = 8,
		DataKit = 9,
		Ccitt = 10,
		Sna = 11,
		DecNet = 12,
		DataLink = 13,
		Lat = 14,
		HyperChannel = 15,
		AppleTalk = 16,
		NetBios = 17,
		VoiceView = 18,
		FireFox = 19,
		//Unknown1 = 20,
		Banyan = 21,
		Atm = 22,
		InterNetworkV6 = 23,
		Cluster = 24,
		Ieee12844 = 25,
		AtmIrda = 26,

		NetworkDesigners = 28,
		Max = 29,

		//Packet = 65536,
		//ControllerAreaNetwork = 65537,
	};
}
#endif
