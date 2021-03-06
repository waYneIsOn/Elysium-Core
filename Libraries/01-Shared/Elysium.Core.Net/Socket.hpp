/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
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

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETFLAGS
#include "SocketFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_IPPROTECTIONLEVEL
#include "IPProtectionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SELECTMODE
#include "SelectMode.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_DELEGATE
#include "../Elysium.Core/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ACCEPTASYNCRESULT
#include "AcceptAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SENDRECEIVEASYNCRESULT
#include "SendReceiveAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETERROR
#include "SocketError.hpp"
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

#ifndef _MSWSOCK_
#include <MSWSock.h>
#endif
#elif defined(__ANDROID__)

#else
#error "undefined os"
#endif

namespace Elysium::Core::Threading
{
	class ThreadPool;
}

namespace Elysium::Core::Net::Sockets
{
	class ELYSIUM_CORE_NET_API Socket final
	{
		friend class Elysium::Core::Threading::ThreadPool;
	public:
		Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType);
		Socket(const Socket& Source) = delete;
		Socket(Socket&& Right);
		~Socket();

		Socket& operator=(const Socket& Source) = delete;
		Socket& operator=(Socket&& Right) noexcept;

		const AddressFamily& GetAddressFamily() const;
		const SocketType& GetSocketType() const;
		const ProtocolType& GetProtocolType() const;

		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const Elysium::Core::int32_t OptionLength);

		const Elysium::Core::int32_t GetAvailable() const;
		const bool GetBlocking() const;
		const bool GetIsConnected() const;
		const Elysium::Core::int32_t GetReceiveTimeout() const;
		const Elysium::Core::int32_t GetSendTimeout() const;
		const Elysium::Core::int32_t GetReceiveBufferSize() const;
		const Elysium::Core::int32_t GetSendBufferSize() const;

		void SetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const bool OptionValue);
		void SetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const Elysium::Core::int32_t OptionValue);

		void SetIPProtectionLevel(const IPProtectionLevel Level);

		void SetReceiveTimeout(const Elysium::Core::int32_t Timeout);
		void SetSendTimeout(const Elysium::Core::int32_t Timeout);
		void SetReceiveBufferSize(const Elysium::Core::int32_t BufferSize);
		void SetSendBufferSize(const Elysium::Core::int32_t BufferSize);

		void SetBlocking(const bool Value);

		const Elysium::Core::int32_t IOControl(const IOControlCode ControlCode, const Elysium::Core::uint32_t OptionInValue, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength);
		const Elysium::Core::int32_t IOControl(const IOControlCode ControlCode, const Elysium::Core::byte * OptionInValue, const size_t OptionInValueLength, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength);
		const Elysium::Core::int32_t IOControl(const Elysium::Core::int32_t ControlCode, const Elysium::Core::byte * OptionInValue, const size_t OptionInValueLength, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength);

		static void Select(Elysium::Core::Collections::Template::List<const Socket*>* CheckRead, Elysium::Core::Collections::Template::List<const Socket*>* CheckWrite, Elysium::Core::Collections::Template::List<const Socket*>* CheckError, const Elysium::Core::int32_t MicroSeconds);
		static void Select(Elysium::Core::Collections::Template::List<const Socket*>* CheckRead, Elysium::Core::Collections::Template::List<const Socket*>* CheckWrite, Elysium::Core::Collections::Template::List<const Socket*>* CheckError, const Elysium::Core::TimeSpan Duration);

		const bool Poll(const Elysium::Core::int32_t MicroSeconds, const SelectMode Mode);
		const bool Poll(const Elysium::Core::TimeSpan Duration, const SelectMode Mode);

		void Connect(const String& Host, const Elysium::Core::int32_t Port);
		void Connect(const Elysium::Core::Net::EndPoint& RemoteEndPoint);
		void Shutdown(const SocketShutdown Value);
		void Disconnect(const bool ReuseSocket);
		void Close();

		void Bind(const Elysium::Core::Net::EndPoint& LocalEndPoint);
		void Listen(const Elysium::Core::int32_t Backlog);
		Socket Accept();

		const size_t Receive(const Elysium::Core::byte* Buffer, const size_t Count);

		const size_t ReceiveFrom(const Elysium::Core::byte* Buffer, const size_t Count, EndPoint& RemoteEndpoint);
		const size_t ReceiveFrom(const Elysium::Core::byte* Buffer, const size_t Count, const SocketFlags SocketFlags, EndPoint& RemoteEndpoint);

		const size_t Send(const Elysium::Core::byte* Buffer, const size_t Count);

		const size_t SendTo(const Elysium::Core::byte* Buffer, const size_t Count, const EndPoint& RemoteEndpoint);
		const size_t SendTo(const Elysium::Core::byte* Buffer, const size_t Count, const SocketFlags SocketFlags, const EndPoint& RemoteEndpoint);

		const AcceptAsyncResult* BeginAccept(const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State);
		Socket EndAccept(const Elysium::Core::IAsyncResult* Result);
		
		const Elysium::Core::IAsyncResult* BeginConnect(const Elysium::Core::Net::EndPoint& RemoteEndPoint, 
			const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State);
		void EndConnect(const Elysium::Core::IAsyncResult* Result, Elysium::Core::Net::Sockets::SocketError& ErrorCode);

		const Elysium::Core::IAsyncResult* BeginDisconnect(const bool ReuseSocket, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback,
			const void* State);
		void EndDisconnect(const Elysium::Core::IAsyncResult* Result);

		// ToDo: BeginReceiveFrom and BeginSendTo
		
		const Elysium::Core::IAsyncResult* BeginReceive(const Elysium::Core::byte* Buffer, const size_t Size, SocketFlags Flags,
			const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State);
		const size_t EndReceive(const Elysium::Core::IAsyncResult* Result, Elysium::Core::Net::Sockets::SocketError& ErrorCode);

		const Elysium::Core::IAsyncResult* BeginSend(const Elysium::Core::byte* Buffer, const size_t Size, SocketFlags Flags,
			const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State);
		const size_t EndSend(const Elysium::Core::IAsyncResult* Result, Elysium::Core::Net::Sockets::SocketError& ErrorCode);
	private:
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		Socket(SOCKET WinSocketHandle);

		static void InitializeWinSockAPI();

		SOCKET _WinSocketHandle;
		PTP_IO _CompletionPortHandle;

		// these need to be obtained during runtime!
		LPFN_CONNECTEX ConnectEx;	
		LPFN_DISCONNECTEX DisconnectEx;

		void RetrieveFunctions();
#elif defined(__ANDROID__)

#else

#endif
		bool _IsConnected = false;
		bool _IsClosed = false;
		bool _IsBlocking = true;

		static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);

		//static void SendCallback(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
		//static void ReceiveCallback(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
	};
}
#endif
