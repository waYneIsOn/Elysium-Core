/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_IPADDRESS
#define ELYSIUM_CORE_NET_IPADDRESS

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			class ELYSIUM_CORE_NET_API IPAddress final
			{
			public:
				IPAddress(const byte* Address, size_t AddressSize);
				IPAddress(const unsigned __int64 NewAddress);
				~IPAddress();

				static const IPAddress& Any();
				//static const IPAddress* Broadcast();
				//static const IPAddress* IPv6Any();
				//static const IPAddress* IPv6Loopback();
				//static const IPAddress* IPv6None();
				//static const IPAddress* Loopback();
				//static const IPAddress* None();

				Sockets::AddressFamily GetAddressFamily() const;
			private:
				const int WriteableOffset = 2;
				const int MaxSize = 30;	// two bytes less than SocketAddress since we're not storing the port

				// byte 0-1: AddressFamily
				// byte rest: ip address
				byte _Data[30];
			};
		}
	}
}
#endif
