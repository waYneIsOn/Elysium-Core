/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETADDRESS
#define ELYSIUM_CORE_NET_SOCKETADDRESS

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#pragma warning(disable : 4251)

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				class Socket;
			}
			
			class ELYSIUM_CORE_NET_API SocketAddress
			{
				friend class Sockets::Socket;
			public:
				SocketAddress(Elysium::Core::Net::Sockets::AddressFamily AddressFamily, int Size);
				SocketAddress(Elysium::Core::Net::Sockets::AddressFamily AddressFamily);
				~SocketAddress();

				Elysium::Core::Net::Sockets::AddressFamily GetFamily();
				int GetPort();
				unsigned int GetSize();
			private:
				SocketAddress();

				const int IPv6AddressSize = 28;
				const int IPv4AddressSize = 16;

				const int WriteableOffset = 2;
				const int MaxSize = 32;

				unsigned int _Size;
				std::vector<byte> _Data;	// byte 0 and 1: AddressFamily; byte 2 and 3: Port; rest ipaddress
			};
		}
	}
}
#endif
