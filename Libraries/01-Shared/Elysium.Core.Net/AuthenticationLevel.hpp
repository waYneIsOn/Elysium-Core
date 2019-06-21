/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_AUTHENTICATIONLEVEL
#define ELYSIUM_CORE_NET_SECURITY_AUTHENTICATIONLEVEL

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				enum class AuthenticationLevel : int
				{
					None = 0,
					MutualAuthRequested = 1,
					MutualAuthRequired = 2
				};
			}
		}
	}
}
#endif
