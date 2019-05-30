/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_ENDPOINT
#define ELYSIUM_CORE_NET_ENDPOINT

#ifndef ELYSIUM_CORE_EXPORT
#include "../Elysium.Core/Export.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETADDRESS
#include "SocketAddress.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			class EXPORT EndPoint
			{
			public:
				virtual ~EndPoint() {};

				Elysium::Core::Net::Sockets::AddressFamily GetAddressFamily() const;

				void Create(Elysium::Core::Net::SocketAddress* Address, Elysium::Core::Net::EndPoint* EndPoint);
				Elysium::Core::Net::EndPoint* Create(Elysium::Core::Net::SocketAddress* Address);
			protected:
				EndPoint();
			private:
				Elysium::Core::Net::Sockets::AddressFamily _AddressFamily;
			};
		}
	}
}
#endif
