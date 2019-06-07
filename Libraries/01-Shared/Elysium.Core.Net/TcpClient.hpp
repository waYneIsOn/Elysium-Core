/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_TCPCLIENT
#define ELYSIUM_CORE_NET_SOCKETS_TCPCLIENT

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "Socket.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_NETWORKSTREAM
#include "NetworkStream.hpp"
#endif

using std::string;

namespace Elysium
{
	namespace Core
	{
		namespace Net
		{
			namespace Sockets
			{
				/// <summary>
				/// 
				/// </summary>
				class ELYSIUM_CORE_NET_API TcpClient
				{
				public:
					// constructors & destructor
					TcpClient();
					~TcpClient();

					// properties - getter
					Socket* GetClient();

					// properties - setter
					// ...

					// methods
					NetworkStream* GetStream();

					void Connect(const string& Host, int Port);
					void Close();
				private:
					Socket _Socket;
					NetworkStream _Stream;
				};
			}
		}
	}
}
#endif
