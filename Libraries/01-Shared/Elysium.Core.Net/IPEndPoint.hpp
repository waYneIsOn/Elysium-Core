/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_IPENDPOINT
#define ELYSIUM_CORE_NET_IPENDPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_ENDPOINT
#include "EndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_IPADDRESS
#include "IPAddress.hpp"
#endif

namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API IPEndPoint final : public EndPoint
	{
	public:
		IPEndPoint(const IPAddress& Address, const Elysium::Core::uint16_t Port);
		IPEndPoint(const IPEndPoint& Source) = delete;
		IPEndPoint(IPEndPoint&& Right) noexcept = delete;
		virtual ~IPEndPoint();

		IPEndPoint& operator=(const IPEndPoint& Source) = delete;
		IPEndPoint& operator=(IPEndPoint&& Right) noexcept = delete;

		virtual const Elysium::Core::Net::Sockets::AddressFamily GetAddressFamily() const override;
		const int GetPort() const;
	protected:
		virtual const Elysium::Core::Net::SocketAddress Serialize() const override;
	private:
		IPAddress _Address;
		Elysium::Core::uint16_t _Port;
	};
}
#endif
