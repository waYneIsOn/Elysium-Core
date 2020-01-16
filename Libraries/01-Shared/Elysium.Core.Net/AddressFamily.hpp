/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#define ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Sockets
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class AddressFamily : uint32_t
#elif defined(__ANDROID__)
	enum class AddressFamily
#else
#error "undefined os"
#endif
	{
		AppleTalk,
		Atm,
		Banyan,
		Ccitt,
		Chaos,
		Cluster,
		DataKit,
		DataLink,
		DecNet,
		Ecma,
		FireFox,
		HyperChannel,
		Ieee12844,
		ImpLink,
		InterNetwork,
		InterNetworkV6,
		Ipx,
		AtmIrda,
		Iso,
		Lat,
		Max,
		NetBios,
		NetworkDesigners,
		NS,
		Osi,
		Pup,
		Sna,
		Unix,
		Unknown,
		Unspecified,
		VoiceView,
	};
}
#endif
