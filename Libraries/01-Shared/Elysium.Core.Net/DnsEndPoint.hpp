/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_DNSENDPOINT
#define ELYSIUM_CORE_NET_DNSENDPOINT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_NET_ENDPOINT
#include "EndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API DnsEndPoint final : public EndPoint
	{
	public:
		DnsEndPoint(const Elysium::Core::Utf8String& Host, const Elysium::Core::uint16_t Port, const Sockets::AddressFamily AddressFamily);
		DnsEndPoint(const DnsEndPoint& Source) = delete;
		DnsEndPoint(DnsEndPoint&& Right) noexcept = delete;
		virtual ~DnsEndPoint();

		DnsEndPoint& operator=(const DnsEndPoint& Source) = delete;
		DnsEndPoint& operator=(DnsEndPoint&& Right) noexcept = delete;

		virtual const Elysium::Core::Net::Sockets::AddressFamily GetAddressFamily() const override;
		const Elysium::Core::Utf8String& GetHost() const;
		const Elysium::Core::uint16_t GetPort() const;

	protected:
		virtual const Elysium::Core::Net::SocketAddress Serialize() const override;
	private:
		const Elysium::Core::Utf8String _Host;
		const Elysium::Core::uint16_t _Port;
		const Sockets::AddressFamily _AddressFamily;
	};
}
#endif
