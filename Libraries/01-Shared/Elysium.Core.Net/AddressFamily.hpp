/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#define ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				/// <summary>
				/// 
				/// </summary>
				enum class AddressFamily : int
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
		}
	}
}
#endif
