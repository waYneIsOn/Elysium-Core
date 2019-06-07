/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#define ELYSIUM_CORE_NET_SOCKETS_SOCKET

#ifndef ELYSIUM_CORE_NET_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETTYPE
#include "SocketType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_PROTOCOLTYPE
#include "ProtocolType.hpp"
#endif

#ifndef _XSTRING_
#include <string>
#endif

#ifndef ELYSIUM_CORE_NET_ENDPOINT
#include "EndPoint.hpp"
#endif

#ifndef _WINSOCK2API_
#if defined(__ANDROID__)
// ToDo ...
#elif defined(_WIN32)
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#error "undefined os"
#endif
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
				// https://docs.microsoft.com/en-us/windows/desktop/winsock/complete-server-code
				// https://docs.microsoft.com/en-us/windows/desktop/winsock/complete-client-code
				class ELYSIUM_CORE_NET_API Socket
				{
				public:
					// constructors & destructor
					Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType);
					~Socket();

					// properties - getter
					AddressFamily GetAddressFamily();
					SocketType GetSocketType();
					ProtocolType GetProtocolType();

					int GetAvailable();
					bool GetIsConnected();
					int GetReceiveTimeout();
					int GetSendTimeout();
					int GetReceiveBufferSize();
					int GetSendBufferSize();

					// properties - setter
					void SetReceiveTimeout(int Timeout);
					void SetSendTimeout(int Timeout);
					void SetReceiveBufferSize(int BufferSize);
					void SetSendBufferSize(int BufferSize);

					// methods
					void Connect(const string& Host, int Port);
					void Connect(const EndPoint& RemoteEndPoint);
					void Disconnect(bool ReuseSocket);

					void Bind(const EndPoint& LocalEndPoint);
					void Listen(const int Backlog);
					void Accept(Socket* ConnectedClient);

					int Send(const byte* Buffer, const int Offset, const int Count);
					int Receive(byte* Buffer, const int Offset, const int Count);
				private:
					// fields
					AddressFamily _AddressFamily;
					SocketType _SocketType;
					ProtocolType _ProtocolType;

#if defined(__ANDROID__)
					// ToDo ...
#elif defined(_WIN32)
					Socket(SOCKET WinSocketHandle, AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType);

					SOCKET _WinSocketHandle;
#else
#error "undefined os"
#endif

					bool _IsConnected = false;
				};
			}
		}
	}
}
#endif
