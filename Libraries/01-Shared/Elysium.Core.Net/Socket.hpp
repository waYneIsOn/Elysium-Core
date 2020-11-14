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
	/*
	Delegate<void>::CreateDelegate<ThreadTests, &ThreadTests::ZeroParameterThreadStart>(*this)
	const Delegate<void, void*>& ParameterizedThreadStart
	*/
	// https://docs.microsoft.com/en-us/windows/desktop/winsock/complete-server-code
	// https://docs.microsoft.com/en-us/windows/desktop/winsock/complete-client-code
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
		void Connect(const EndPoint& RemoteEndPoint);
		void Shutdown(const SocketShutdown Value);
		void Disconnect(const bool ReuseSocket);
		void Close();

		void Bind(const EndPoint& LocalEndPoint);
		void Listen(const Elysium::Core::int32_t Backlog);
		const Socket Accept();

		const size_t Send(const Elysium::Core::byte* Buffer, const size_t Count) const;

		const size_t SendTo(const Elysium::Core::byte* Buffer, const size_t Count, const EndPoint& RemoteEndpoint) const;
		const size_t SendTo(const Elysium::Core::byte* Buffer, const size_t Count, const SocketFlags SocketFlags, const EndPoint& RemoteEndpoint) const;

		const size_t Receive(const Elysium::Core::byte* Buffer, const size_t Count) const;

		const size_t ReceiveFrom(const Elysium::Core::byte* Buffer, const size_t Count, EndPoint& RemoteEndpoint) const;
		const size_t ReceiveFrom(const Elysium::Core::byte* Buffer, const size_t Count, const SocketFlags SocketFlags, EndPoint& RemoteEndpoint) const;
		
		const SendReceiveAsyncResult* BeginReceive(const Elysium::Core::byte* Buffer, const size_t Size, SocketFlags Flags,
			const Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State) const;
		const size_t EndReceive(const Elysium::Core::IAsyncResult* Result, Elysium::Core::Net::Sockets::SocketError& ErrorCode) const;
	private:
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		Socket(SOCKET WinSocketHandle);

		static void InitializeWinSockAPI();

		SOCKET _WinSocketHandle;
		PTP_IO _CompletionPortHandle;
#elif defined(__ANDROID__)

#else

#endif
		bool _IsConnected = false;
		bool _IsClosed = false;
		bool _IsBlocking = true;

		static void Callback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);
	};
}
#endif
