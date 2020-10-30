/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACETYPE
#define ELYSIUM_CORE_NET_NETWORKINFORMATION_NETWORKINTERFACETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::NetworkInformation
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class NetworkInterfaceType : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class NetworkInterfaceType
#else
#error "undefined os"
#endif
	{
		Unknown = 1,

		Ethernet = 6,

		TokenRing = 9,

		Fddi = 15,

		BasicIsdn = 20,

		PrimaryIsdn = 21,

		Ppp = 23,

		Loopback = 24,

		Ethernet3Megabit = 26,

		Slip = 28,

		Atm = 37,

		GenericModem = 48,

		FastEthernetT = 62,

		Isdn = 63,

		FastEthernetFx = 69,

		Wireless80211 = 71,

		AsymmetricDsl = 94,

		RateAdaptDsl = 95,

		SymmetricDsl = 96,

		VeryHighDpeedDsl = 97,

		IPOverAtm = 144,

		GigabitEthernet = 117,

		Tunnel = 131,

		MultiRateSymmetricDsl = 143,

		HighPerformanceSerialBus = 144,

		Wman = 237,

		Wwanpp = 243,

		Wwanpp2 = 244
	};
}
#endif
