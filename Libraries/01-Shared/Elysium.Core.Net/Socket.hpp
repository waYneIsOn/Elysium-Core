/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#define ELYSIUM_CORE_NET_SOCKETS_SOCKET

#ifdef _MSC_VER
#pragma once
#endif

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

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETOPTIONLEVEL
#include "SocketOptionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETOPTIONNAME
#include "SocketOptionName.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_IOCONTROLCODE
#include "IOControlCode.hpp"
#endif

#if defined(__ANDROID__)
// ToDo ...
#elif defined(_WIN32)

#ifndef _WINSOCK2API_
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

#else
#error "undefined os"
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
		Socket(const Socket& Source) = delete;
		Socket(Socket&& Right) noexcept = delete;
		~Socket();

		Socket& operator=(const Socket& Source) = delete;
		Socket& operator=(Socket&& Right) noexcept = delete;

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
		void SetReceiveTimeout(const Elysium::Core::int32_t Timeout);
		void SetSendTimeout(const Elysium::Core::int32_t Timeout);
		void SetReceiveBufferSize(const Elysium::Core::int32_t BufferSize);
		void SetSendBufferSize(const Elysium::Core::int32_t BufferSize);

		// methods
		void Connect(const String& Host, const Elysium::Core::int32_t Port);
		void Connect(const EndPoint& RemoteEndPoint);
		void Close();
		void Shutdown(const SocketShutdown Value);
		void Disconnect(const bool ReuseSocket);

		void Bind(const EndPoint& LocalEndPoint);
		void Listen(const int Backlog);
		const Socket Accept();

		const Elysium::Core::int32_t IOControl(const IOControlCode ControlCode, const Elysium::Core::byte * OptionInValue, const size_t OptionInValueLength, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength);
		const Elysium::Core::int32_t IOControl(const IOControlCode ControlCode, const Elysium::Core::uint32_t OptionInValue, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength);

		void SetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const bool OptionValue);
		void SetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const Elysium::Core::int32_t OptionValue);

		const size_t Send(const Elysium::Core::byte* Buffer, const size_t Count) const;
		const size_t Receive(Elysium::Core::byte* Buffer, const size_t Count) const;
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
