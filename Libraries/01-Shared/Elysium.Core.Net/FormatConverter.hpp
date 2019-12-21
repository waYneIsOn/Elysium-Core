/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_FORMATCONVERTER
#define ELYSIUM_CORE_NET_FORMATCONVERTER
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE
#include "ProtocolType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE
#include "SocketType.hpp"
#endif

#ifndef _WINSOCK2API_
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

namespace Elysium::Core::Net
{
	class FormatConverter
	{
	public:
		static int Convert(Elysium::Core::Net::Sockets::AddressFamily AddressFamily);
		static int Convert(Elysium::Core::Net::Sockets::ProtocolType ProtocolType);
		static int Convert(Elysium::Core::Net::Sockets::SocketType SocketType);

		static Elysium::Core::Net::Sockets::AddressFamily Convert(ADDRESS_FAMILY WinAddressFamily);
	private:
		FormatConverter();
		~FormatConverter();
	};
}
