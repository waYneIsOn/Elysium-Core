/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_PROTECTIONLEVEL
#define ELYSIUM_CORE_NET_SECURITY_PROTECTIONLEVEL

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				enum class ProtectionLevel : int
				{
					None = 0,
					Sign = 1,
					EncryptAndSign = 2
				};
			}
		}
	}
}
#endif
