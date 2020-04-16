/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef _XSTRING_
#include <xstring>
#endif
/*
namespace Elysium::Core::Net
{
	class ELYSIUM_CORE_NET_API DnsEndPoint final : public EndPoint
	{
	public:
		DnsEndPoint(const std::string& Host, const int Port);
		~DnsEndPoint();

		std::string GetHost() const;
		int GetPort() const;

		virtual void Serialize(SocketAddress* Address) const override;
	private:
		std::string _Host;
		int _Port;
	};
}
*/
#endif
