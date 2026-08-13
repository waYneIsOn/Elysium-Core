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

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKET
#include "../Elysium.Core.Template/Net/Sockets/Socket.hpp"
#endif








#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_ADDRESSFAMILY
#include "../Elysium.Core.Template/Net/Sockets/AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETTYPE
#include "../Elysium.Core.Template/Net/Sockets/SocketType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_PROTOCOLTYPE
#include "../Elysium.Core.Template/Net/Sockets/ProtocolType.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_DNSENDPOINT
#include "DnsEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_IPENDPOINT
#include "IPEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETSHUTDOWN
#include "../Elysium.Core.Template/Net/Sockets/SocketShutdown.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETOPTIONLEVEL
#include "../Elysium.Core.Template/Net/Sockets/SocketOptionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETOPTIONNAME
#include "../Elysium.Core.Template/Net/Sockets/SocketOptionName.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_IOCONTROLCODE
#include "../Elysium.Core.Template/Net/Sockets/IOControlCode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETFLAGS
#include "../Elysium.Core.Template/Net/Sockets/SocketFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_IPPROTECTIONLEVEL
#include "../Elysium.Core.Template/Net/Sockets/IPProtectionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SELECTMODE
#include "../Elysium.Core.Template/Net/Sockets/SelectMode.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_ACCEPTASYNCRESULT
#include "AcceptAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SENDRECEIVEASYNCRESULT
#include "SendReceiveAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETERROR
#include "../Elysium.Core.Template/Net/Sockets/SocketError.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#include "../Elysium.Core.Template/Memory/UniquePointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../Elysium.Core.Template/System/OperatingSystem.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

#ifndef _MSWSOCK_
#include <MSWSock.h>
#endif

#pragma comment(lib, "ws2_32.lib")
#else
#error "undefined os"
#endif

namespace Elysium::Core::Net::Sockets
{
	/*
	class ELYSIUM_CORE_NET_API Elysium::Core::Template::Exceptions::Net::Sockets::Socket;

	using Socket = Elysium::Core::Template::Exceptions::Net::Sockets::Socket;
	*/


	class ELYSIUM_CORE_NET_API Socket final
	{
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		Socket(SOCKET WinSocketHandle);
#endif
	public:
		Socket(Elysium::Core::Template::Net::Sockets::AddressFamily AddressFamily, Elysium::Core::Template::Net::Sockets::SocketType SocketType, Elysium::Core::Template::Net::Sockets::ProtocolType ProtocolType);

		Socket(const Socket& Source) = delete;

		Socket(Socket&& Right) noexcept;

		~Socket();
	public:
		Socket& operator=(const Socket& Source) = delete;

		Socket& operator=(Socket&& Right) noexcept;
	public:
		const Elysium::Core::Template::Net::Sockets::AddressFamily GetAddressFamily() const;

		const Elysium::Core::Template::Net::Sockets::SocketType GetSocketType() const;

		const Elysium::Core::Template::Net::Sockets::ProtocolType GetProtocolType() const;

		const Elysium::Core::Container::VectorOfByte GetSocketOption(const Elysium::Core::Template::Net::Sockets::SocketOptionLevel OptionLevel, const Elysium::Core::Template::Net::Sockets::SocketOptionName OptionName, const Elysium::Core::int32_t OptionLength);

		const Elysium::Core::int32_t GetAvailable() const;

		const bool GetBlocking() const;

		const bool GetIsConnected() const;

		const Elysium::Core::int32_t GetReceiveTimeout() const;

		const Elysium::Core::int32_t GetSendTimeout() const;

		const Elysium::Core::int32_t GetReceiveBufferSize() const;

		const Elysium::Core::int32_t GetSendBufferSize() const;
	public:
		void SetSocketOption(const Elysium::Core::Template::Net::Sockets::SocketOptionLevel OptionLevel, const Elysium::Core::Template::Net::Sockets::SocketOptionName OptionName, const bool OptionValue);

		void SetSocketOption(const Elysium::Core::Template::Net::Sockets::SocketOptionLevel OptionLevel, const Elysium::Core::Template::Net::Sockets::SocketOptionName OptionName, const Elysium::Core::int32_t OptionValue);

		void SetIPProtectionLevel(const Elysium::Core::Template::Net::Sockets::IPProtectionLevel Level);

		void SetReceiveTimeout(const Elysium::Core::int32_t Timeout);

		void SetSendTimeout(const Elysium::Core::int32_t Timeout);

		void SetReceiveBufferSize(const Elysium::Core::int32_t BufferSize);

		void SetSendBufferSize(const Elysium::Core::int32_t BufferSize);

		void SetBlocking(const bool Value);
	public:
		static void Select(Elysium::Core::Template::Container::Vector<Socket*>* CheckRead, Elysium::Core::Template::Container::Vector<Socket*>* CheckWrite, Elysium::Core::Template::Container::Vector<Socket*>* CheckError, const Elysium::Core::uint32_t MicroSeconds);

		static void Select(Elysium::Core::Template::Container::Vector<Socket*>* CheckRead, Elysium::Core::Template::Container::Vector<Socket*>* CheckWrite, Elysium::Core::Template::Container::Vector<Socket*>* CheckError, const Elysium::Core::TimeSpan Duration);
	public:
		const Elysium::Core::int32_t IOControl(const Elysium::Core::Template::Net::Sockets::IOControlCode ControlCode, const Elysium::Core::uint32_t OptionInValue, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength);
		
		const Elysium::Core::int32_t IOControl(const Elysium::Core::Template::Net::Sockets::IOControlCode ControlCode, const Elysium::Core::byte * OptionInValue, const Elysium::Core::size OptionInValueLength, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength);
		
		const Elysium::Core::int32_t IOControl(const Elysium::Core::int32_t ControlCode, const Elysium::Core::byte * OptionInValue, const Elysium::Core::size OptionInValueLength, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength);

		const bool Poll(const Elysium::Core::int32_t MicroSeconds, const Elysium::Core::Template::Net::Sockets::SelectMode Mode);
		
		const bool Poll(const Elysium::Core::TimeSpan Duration, const Elysium::Core::Template::Net::Sockets::SelectMode Mode);

		void Connect(const Utf8String& Host, const Elysium::Core::uint16_t Port);

		template <class T>
		inline void Connect(const T& RemoteEndPoint)
		{
			/*
			if (GetIsConnected())
			{
				return;
			}
			*/
			/*
			const SocketAddress Address = RemoteEndPoint.Serialize();
			Elysium::Core::int32_t Result;
			if ((Result = connect(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize())) == SOCKET_ERROR)
			{
				//Close();
				throw SocketException();
			}

			_IsConnected = true;
			*/
			throw;
		}

		void Shutdown(const Elysium::Core::Template::Net::Sockets::SocketShutdown Value);

		void Disconnect(const bool ReuseSocket);

		void Close();

		template <class T>
		inline void Bind(const T& LocalEndPoint)
		{
			/*
			const SocketAddress Address = LocalEndPoint.Serialize();
			Elysium::Core::int32_t Result = bind(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize());
			if (Result == SOCKET_ERROR)
			{
				throw SocketException();
			}
			*/
			throw;
		}

		void Listen(const Elysium::Core::int32_t Backlog);

		Socket Accept();

		const Elysium::Core::size Receive(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count);

		//const Elysium::Core::size ReceiveFrom(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count, EndPoint& RemoteEndpoint);

		//const Elysium::Core::size ReceiveFrom(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count, const SocketFlags SocketFlags, EndPoint& RemoteEndpoint);

		const Elysium::Core::size Send(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count);

		//const Elysium::Core::size SendTo(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count, const EndPoint& RemoteEndpoint);

		//const Elysium::Core::size SendTo(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count, const SocketFlags SocketFlags, const EndPoint& RemoteEndpoint);
	public:
		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginAccept(
			const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback, const void* State);

		const Socket EndAccept(const Elysium::Core::IAsyncResult* AsyncResult);

		template <class T>
		inline Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginConnect(
			const T& RemoteEndPoint, const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback,
			const void* State)
		{	// @ToDo
			/*
			// ConnectEx requires the socket to be bound!
			Elysium::Core::Net::IPEndPoint LocalEndPoint = Elysium::Core::Net::IPEndPoint(Elysium::Core::Net::IPAddress::Any(), 0);
			Bind(LocalEndPoint);

			SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(*this, Callback, State);
			AsyncResult->_WSABuffer.len = 0;
			AsyncResult->_WSABuffer.buf = nullptr;

			StartThreadpoolIo(_CompletionPortHandle);
			const SocketAddress Address = RemoteEndPoint.Serialize();
			bool Result = ConnectEx(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize(), nullptr, 0, nullptr, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap);
			if (!Result)
			{
				if (WSAGetLastError() != static_cast<Elysium::Core::int32_t>(SocketError::IOPending))
				{
					CancelThreadpoolIo(_CompletionPortHandle);
					delete AsyncResult;
					throw SocketException();
				}
			}

			return Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult>(AsyncResult);
			*/
			throw;
		}

		void EndConnect(const Elysium::Core::IAsyncResult* AsyncResult, Elysium::Core::Template::Net::Sockets::SocketError& ErrorCode);

		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginDisconnect(const bool ReuseSocket,
			const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback, const void* State);

		void EndDisconnect(const Elysium::Core::IAsyncResult* AsyncResult);

		// ToDo: BeginReceiveFrom and BeginSendTo
		
		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginReceive(const Elysium::Core::byte* Buffer,
			const Elysium::Core::size Size, Elysium::Core::Template::Net::Sockets::SocketFlags Flags, const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback,
			const void* State);

		const Elysium::Core::size EndReceive(const Elysium::Core::IAsyncResult* AsyncResult, Elysium::Core::Template::Net::Sockets::SocketError& ErrorCode);

		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginSend(const Elysium::Core::byte* Buffer,
			const Elysium::Core::size Size, Elysium::Core::Template::Net::Sockets::SocketFlags Flags,
			const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback, const void* State);

		const Elysium::Core::size EndSend(const Elysium::Core::IAsyncResult* AsyncResult, Elysium::Core::Template::Net::Sockets::SocketError& ErrorCode);
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		SOCKET _WinSocketHandle;
		PTP_IO _CompletionPortHandle;

		LPFN_CONNECTEX ConnectEx;
		LPFN_DISCONNECTEX DisconnectEx;

		static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);
#endif
		bool _IsConnected = false;
		bool _IsClosed = false;
		bool _IsBlocking = true;

		//static void SendCallback(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
		//static void ReceiveCallback(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
	};
}
#endif
