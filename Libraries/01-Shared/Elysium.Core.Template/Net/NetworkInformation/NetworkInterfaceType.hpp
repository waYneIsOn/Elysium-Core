/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_NETWORKINFORMATION_NETWORKINTERFACECOMPONENT
#define ELYSIUM_CORE_TEMPLATE_NET_NETWORKINFORMATION_NETWORKINTERFACECOMPONENT

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
	enum class NetworkInterfaceType
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
#pragma once
