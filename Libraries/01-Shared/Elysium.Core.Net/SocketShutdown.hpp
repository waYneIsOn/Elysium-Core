/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETSHUTDOWN
#define ELYSIUM_CORE_NET_SOCKETS_SOCKETSHUTDOWN

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				enum class SocketShutdown : int
				{
					Receive = 0,
					Send = 1,
					Both = 2
				};
			}
		}
	}
}
#endif
