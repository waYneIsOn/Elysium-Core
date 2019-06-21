/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_SSLPOLICYERRORS
#define ELYSIUM_CORE_NET_SECURITY_SSLPOLICYERRORS

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				enum class SslPolicyErrors : int
				{
					None = 0,
					RemoteCertificateNotAvailable = 1,
					RemoteCertificateNameMismatch = 2,
					RemoteCertificateChainErrors = 4
				};

				inline SslPolicyErrors operator|(SslPolicyErrors lhs, SslPolicyErrors rhs)
				{
					return static_cast<SslPolicyErrors>(static_cast<int>(lhs) | static_cast<int>(rhs));
				}
				inline SslPolicyErrors operator&(SslPolicyErrors lhs, SslPolicyErrors rhs)
				{
					return static_cast<SslPolicyErrors>(static_cast<int>(lhs) & static_cast<int>(rhs));
				}
			}
		}
	}
}
#endif
