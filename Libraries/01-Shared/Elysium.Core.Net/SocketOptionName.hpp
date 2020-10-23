/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETOPTIONNAME
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETOPTIONNAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class SocketOptionName : Elysium::Core::uint32_t
#elif defined(__ANDROID__)
	enum class SocketOptionName
#else
#error "undefined os"
#endif
	{
		DontLinger = -129,

		ExclusiveAddressUse = -5,

		Debug = 1,

		IPOptions = 1,

		NoDelay = 1,

		NoChecksum = 1,

		AcceptConnection = 2,

		HeaderIncluded = 2,

		BsdUrgent = 2,

		Expedited = 2,

		TypeOfService = 3,

		ReuseAddress = 4,

		IpTimeToLive = 4,

		KeepAlive = 8,

		MulticastInterface = 9,

		MulticastTimeToLive = 10,

		MulticastLoopback = 11,

		AddMembership = 12,

		DropMembership = 13,

		DontFragment = 14,

		AddSourceMembership = 15,

		DontRoute = 16,

		DropSourceMembership = 16,

		BlockSource = 17,

		UnblockSource = 18,

		PacketInformation = 19,

		ChecksumCoverage = 20,

		HopLimit = 21,

		IPProtectionLevel = 23,

		IPv6Only = 27,

		Broadcast = 32,

		UseLoopback = 64,

		Linger = 128,

		OutOfBandInline = 256,

		SendBuffer = 4097,

		ReceiveBuffer = 4098,

		SendLowWater = 4099,

		ReceiveLowWater = 4100,

		SendTimeout = 4101,

		ReceiveTimeout = 4102,

		Error = 4103,

		Type = 4104,

		ReuseUnicastPort = 12295,

		UpdateAcceptContext = 28683,

		UpdateConnectContext = 28688,

		MaxConnections = Elysium::Core::UInt32::GetMaxValue()
	};
}

#endif
