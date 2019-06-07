/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_IPENDPOINT
#define ELYSIUM_CORE_NET_IPENDPOINT

#ifndef ELYSIUM_CORE_NET_ENDPOINT
#include "EndPoint.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			class ELYSIUM_CORE_NET_API IPEndPoint final : public EndPoint
			{
			public:
				IPEndPoint(const IPAddress& Address, const int Port);
				~IPEndPoint();

				const IPAddress& GetAddress() const;
				const int GetPort() const;

				virtual void Serialize(SocketAddress* Address) const override;
			private:
				int _Port;
			};
		}
	}
}
#endif
