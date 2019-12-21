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

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_ENDPOINT
#include "EndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETSHUTDOWN
#include "SocketShutdown.hpp"
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

namespace Elysium::Core::Net::Sockets
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
		AddressFamily GetAddressFamily() const;
		SocketType GetSocketType() const;
		ProtocolType GetProtocolType() const;

		int GetAvailable() const;
		bool GetBlocking() const;
		bool GetIsConnected() const;
		int GetReceiveTimeout() const;
		int GetSendTimeout() const;
		int GetReceiveBufferSize() const;
		int GetSendBufferSize() const;

		// properties - setter
		void SetReceiveTimeout(int Timeout);
		void SetSendTimeout(int Timeout);
		void SetReceiveBufferSize(int BufferSize);
		void SetSendBufferSize(int BufferSize);

		// methods
		void Connect(const String& Host, int Port);
		void Connect(const EndPoint& RemoteEndPoint);
		void Shutdown(SocketShutdown Value);
		void Disconnect(bool ReuseSocket);

		void Bind(const EndPoint& LocalEndPoint);
		void Listen(const int Backlog);
		void Accept(Socket* ConnectedClient);

		size_t Send(const byte* Buffer, const size_t Count);
		size_t Receive(byte* Buffer, const size_t Count);
	private:
		// fields
		AddressFamily _AddressFamily;
		SocketType _SocketType;
		ProtocolType _ProtocolType;

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		Socket(SOCKET WinSocketHandle, AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType);
		SOCKET _WinSocketHandle;
#elif defined(__ANDROID__)

#else

#endif
		bool _IsConnected = false;
	};
}
#endif
