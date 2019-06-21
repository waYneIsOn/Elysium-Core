/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_ENCRYPTIONPOLICY
#define ELYSIUM_CORE_NET_SECURITY_ENCRYPTIONPOLICY

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				enum class EncryptionPolicy : int
				{
					RequireEncryption = 0,
					AllowNoEncryption = 1,
					NoEncryption = 2
				};
			}
		}
	}
}
#endif
