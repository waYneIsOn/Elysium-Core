/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_DNSENDPOINT
#define ELYSIUM_CORE_NET_DNSENDPOINT

#ifndef ELYSIUM_CORE_NET_ENDPOINT
#include "EndPoint.hpp"
#endif

#ifndef _XSTRING_
#include <xstring>
#endif
/*
namespace Elysium
{
	namespace Core
	{
		namespace Net
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
	}
}
*/
#endif
