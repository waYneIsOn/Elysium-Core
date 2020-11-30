/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_ENDPOINT
#define ELYSIUM_CORE_NET_ENDPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETADDRESS
#include "SocketAddress.hpp"
#endif

namespace Elysium::Core::Net
{
	namespace Sockets
	{
		class Socket;
	}

	class ELYSIUM_CORE_NET_API EndPoint
	{
		friend class Sockets::Socket;
	public:
		EndPoint(const EndPoint& Source) = delete;
		EndPoint(EndPoint&& Right) noexcept = delete;
		virtual ~EndPoint();

		EndPoint& operator=(const EndPoint& Source) = delete;
		EndPoint& operator=(EndPoint&& Right) noexcept = delete;

		virtual const Elysium::Core::Net::Sockets::AddressFamily GetAddressFamily() const = 0;
	protected:
		EndPoint();

		virtual const Elysium::Core::Net::SocketAddress Serialize() const = 0;
	};
}
#endif
