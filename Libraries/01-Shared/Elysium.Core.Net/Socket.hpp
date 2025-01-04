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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_TIMESPAN
#include "../Elysium.Core/TimeSpan.hpp"
#endif

#ifndef ELYSIUM_CORE_CONTAINER_VECTOROFBYTE
#include "../Elysium.Core/VectorOfByte.hpp"
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

#ifndef ELYSIUM_CORE_NET_SOCKETS_ACCEPTASYNCRESULT
#include "AcceptAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SENDRECEIVEASYNCRESULT
#include "SendReceiveAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETERROR
#include "SocketError.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#include "../Elysium.Core.Template/UniquePointer.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_NET_SOCKETS_INTERNAL_WINSOCKET
#include "WinSocket.hpp"
#endif
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
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		Socket(SOCKET WinSocketHandle);
#endif
	public:
		Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType);

		Socket(const Socket& Source) = delete;

		Socket(Socket&& Right) noexcept;

		~Socket();
	public:
		Socket& operator=(const Socket& Source) = delete;

		Socket& operator=(Socket&& Right) noexcept;
	public:
		const AddressFamily GetAddressFamily() const;

		const SocketType GetSocketType() const;

		const ProtocolType GetProtocolType() const;

		const Elysium::Core::Container::VectorOfByte GetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const Elysium::Core::int32_t OptionLength);

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
	public:
		static void Select(Elysium::Core::Template::Container::Vector<Socket*>* CheckRead, Elysium::Core::Template::Container::Vector<Socket*>* CheckWrite, Elysium::Core::Template::Container::Vector<Socket*>* CheckError, const Elysium::Core::uint32_t MicroSeconds);

		static void Select(Elysium::Core::Template::Container::Vector<Socket*>* CheckRead, Elysium::Core::Template::Container::Vector<Socket*>* CheckWrite, Elysium::Core::Template::Container::Vector<Socket*>* CheckError, const Elysium::Core::TimeSpan Duration);
	public:
		const Elysium::Core::int32_t IOControl(const IOControlCode ControlCode, const Elysium::Core::uint32_t OptionInValue, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength);
		
		const Elysium::Core::int32_t IOControl(const IOControlCode ControlCode, const Elysium::Core::byte * OptionInValue, const Elysium::Core::size OptionInValueLength, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength);
		
		const Elysium::Core::int32_t IOControl(const Elysium::Core::int32_t ControlCode, const Elysium::Core::byte * OptionInValue, const Elysium::Core::size OptionInValueLength, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength);

		const bool Poll(const Elysium::Core::int32_t MicroSeconds, const SelectMode Mode);
		
		const bool Poll(const Elysium::Core::TimeSpan Duration, const SelectMode Mode);

		void Connect(const Utf8String& Host, const Elysium::Core::uint16_t Port);

		void Connect(const Elysium::Core::Net::EndPoint& RemoteEndPoint);

		void Shutdown(const SocketShutdown Value);

		void Disconnect(const bool ReuseSocket);

		void Close();

		void Bind(const Elysium::Core::Net::EndPoint& LocalEndPoint);

		void Listen(const Elysium::Core::int32_t Backlog);

		Socket Accept();

		const Elysium::Core::size Receive(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count);

		const Elysium::Core::size ReceiveFrom(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count, EndPoint& RemoteEndpoint);

		const Elysium::Core::size ReceiveFrom(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count, const SocketFlags SocketFlags, EndPoint& RemoteEndpoint);

		const Elysium::Core::size Send(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count);

		const Elysium::Core::size SendTo(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count, const EndPoint& RemoteEndpoint);

		const Elysium::Core::size SendTo(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count, const SocketFlags SocketFlags, const EndPoint& RemoteEndpoint);
	public:
		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginAccept(const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State);

		const Socket EndAccept(const Elysium::Core::IAsyncResult* AsyncResult);

		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginConnect(const Elysium::Core::Net::EndPoint& RemoteEndPoint,
			const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State);

		void EndConnect(const Elysium::Core::IAsyncResult* AsyncResult, Elysium::Core::Net::Sockets::SocketError& ErrorCode);

		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginDisconnect(const bool ReuseSocket, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback,
			const void* State);

		void EndDisconnect(const Elysium::Core::IAsyncResult* AsyncResult);

		// ToDo: BeginReceiveFrom and BeginSendTo
		
		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginReceive(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, SocketFlags Flags,
			const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State);

		const Elysium::Core::size EndReceive(const Elysium::Core::IAsyncResult* AsyncResult, Elysium::Core::Net::Sockets::SocketError& ErrorCode);

		Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginSend(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, SocketFlags Flags,
			const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State);

		const Elysium::Core::size EndSend(const Elysium::Core::IAsyncResult* AsyncResult, Elysium::Core::Net::Sockets::SocketError& ErrorCode);
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
