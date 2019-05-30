/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				enum class SocketType : int
				{
					Dgram,
					Raw,
					Rdm,
					Seqpacket,
					Stream,
					Unknown,
				};
			}
		}
	}
}
#endif
