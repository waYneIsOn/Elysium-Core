/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKET
#define ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKET

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NET_SOCKETS_SOCKETEXCEPTION
#include "../../Exceptions/SocketException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_DNSENDPOINT
#include "../DnsEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_IOCONTROLCODE
#include "IOControlCode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_IPPROTECTIONLEVEL
#include "IPProtectionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_PROTOCOLTYPE
#include "ProtocolType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SELECTMODE
#include "SelectMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETFLAGS
#include "SocketFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETOPTIONLEVEL
#include "SocketOptionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETOPTIONNAME
#include "SocketOptionName.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETSHUTDOWN
#include "SocketShutdown.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETTYPE
#include "SocketType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_THREADING_THREADPOOL
#include "../../Threading/ThreadPool.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINSOCK2API_
	#include <WinSock2.h>
	#endif

	#ifndef _MSWSOCK_
	#include <MSWSock.h>
	#endif

	#ifndef _WS2TCPIP_H_
	#include <WS2tcpip.h>
	#endif

	#pragma comment(lib, "ws2_32.lib")
#else
#error "unsupported os"
#endif

namespace Elysium::Core::Template::Net::Sockets
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	class Socket
	{
	public:
		constexpr Socket() = delete;
	private:
		inline constexpr Socket(SOCKET SocketHandle)
			: _SocketHandle(SocketHandle), _CompletionPortHandle(CreateThreadpoolIo(reinterpret_cast<HANDLE>(_SocketHandle), &IOCompletionPortCallback, this, 
				&Elysium::Core::Template::Threading::ThreadPool::GetIOPool()._Environment)), 
			ConnectEx(RetrieveFunctionConnectEx(_SocketHandle)), DisconnectEx(RetrieveFunctionDisconnectEx(_SocketHandle)), _IsConnected(true)
		{ }
	public:
		inline constexpr Socket(const Elysium::Core::Template::Net::Sockets::AddressFamily AddressFamily, const Elysium::Core::Template::Net::Sockets::SocketType SocketType,
			const Elysium::Core::Template::Net::Sockets::ProtocolType ProtocolType)
			: _SocketHandle(CreateWinSocket(AddressFamily, SocketType, ProtocolType)), _CompletionPortHandle(CreateThreadpoolIo(reinterpret_cast<HANDLE>(_SocketHandle),
				&IOCompletionPortCallback, this, &Elysium::Core::Template::Threading::ThreadPool::GetIOPool()._Environment)),
			ConnectEx(RetrieveFunctionConnectEx(_SocketHandle)), DisconnectEx(RetrieveFunctionDisconnectEx(_SocketHandle)), _IsConnected(false)
		{ }

		inline constexpr Socket(const Socket& Source) = delete;

		inline constexpr Socket(Socket&& Right) noexcept = delete;

		inline constexpr ~Socket()
		{
			// @ToDo: this needs to be handled correctly (only close after we've received the "current message", blocking/non-blocking etc.)
			Close();
		}
	public:
		constexpr Socket& operator=(const Socket& Source) = delete;

		constexpr Socket& operator=(Socket&& Right) noexcept = delete;
	public:
		inline const Elysium::Core::Template::Net::Sockets::AddressFamily GetAddressFamily() const
		{
			WSAPROTOCOL_INFO ProtocolInfo{};
			WSADuplicateSocket(_SocketHandle, GetCurrentProcessId(), &ProtocolInfo);
			return static_cast<Elysium::Core::Template::Net::Sockets::AddressFamily>(ProtocolInfo.iAddressFamily);
		}

		inline const Elysium::Core::Template::Net::Sockets::SocketType GetSocketType() const
		{
			WSAPROTOCOL_INFO ProtocolInfo{};
			WSADuplicateSocket(_SocketHandle, GetCurrentProcessId(), &ProtocolInfo);
			return static_cast<Elysium::Core::Template::Net::Sockets::SocketType>(ProtocolInfo.iSocketType);
		}

		inline const Elysium::Core::Template::Net::Sockets::ProtocolType GetProtocolType() const
		{
			WSAPROTOCOL_INFO ProtocolInfo{};
			WSADuplicateSocket(_SocketHandle, GetCurrentProcessId(), &ProtocolInfo);
			return static_cast<Elysium::Core::Template::Net::Sockets::ProtocolType>(ProtocolInfo.iProtocol);
		}

		inline const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> GetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, 
			const Elysium::Core::Template::System::int32_t OptionLength) const
		{
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result(OptionLength);
			if (SOCKET_ERROR == getsockopt(_SocketHandle, static_cast<int>(OptionLevel), static_cast<int>(OptionName), reinterpret_cast<char*>(&Result[0]),
				const_cast<int*>(reinterpret_cast<const int*>(&OptionLength))))
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}
			
			return Result;
		}

		inline const Elysium::Core::Template::System::int32_t GetAvailable() const
		{
			char Buffer;
			Elysium::Core::Template::System::int32_t BytesAvailable = recv(_SocketHandle, &Buffer, 1, MSG_PEEK);
			if (SOCKET_ERROR == BytesAvailable)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			return BytesAvailable;
		}

		inline constexpr const bool GetBlocking() const
		{	// @ToDo
			return false;
		}

		inline constexpr const bool GetIsConnected() const
		{	// @ToDo
			return false;
		}

		inline const Elysium::Core::Template::System::int32_t GetReceiveTimeout() const
		{
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result =
				GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveTimeout, sizeof(Elysium::Core::Template::System::int32_t));

			return *reinterpret_cast<const Elysium::Core::Template::System::int32_t*>(&Result[0]);
		}

		inline const Elysium::Core::Template::System::int32_t GetSendTimeout() const
		{
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result =
				GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendTimeout, sizeof(Elysium::Core::Template::System::int32_t));

			return *reinterpret_cast<const Elysium::Core::Template::System::int32_t*>(&Result[0]);
		}

		inline const Elysium::Core::Template::System::int32_t GetReceiveBufferSize() const
		{
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result =
				GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveBuffer, sizeof(Elysium::Core::Template::System::int32_t));

			return *reinterpret_cast<const Elysium::Core::Template::System::int32_t*>(&Result[0]);
		}

		inline const Elysium::Core::Template::System::int32_t GetSendBufferSize() const
		{
			const Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result =
				GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendBuffer, sizeof(Elysium::Core::Template::System::int32_t));

			return *reinterpret_cast<const Elysium::Core::Template::System::int32_t*>(&Result[0]);
		}
	public:
		inline void SetSocketOption(const Elysium::Core::Template::Net::Sockets::SocketOptionLevel OptionLevel, const Elysium::Core::Template::Net::Sockets::SocketOptionName OptionName,
			const bool OptionValue)
		{
			SetSocketOption(OptionLevel, OptionName, OptionValue == true ? 1 : 0);
		}

		inline void SetSocketOption(const Elysium::Core::Template::Net::Sockets::SocketOptionLevel OptionLevel, const Elysium::Core::Template::Net::Sockets::SocketOptionName OptionName,
			const Elysium::Core::Template::System::int32_t OptionValue)
		{
			if (SOCKET_ERROR == setsockopt(_SocketHandle, static_cast<Elysium::Core::Template::System::int32_t>(OptionLevel),
				static_cast<Elysium::Core::Template::System::int32_t>(OptionName), (char*)&OptionValue, sizeof(OptionValue)))
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}
		}

		inline void SetIPProtectionLevel(const Elysium::Core::Template::Net::Sockets::IPProtectionLevel Level)
		{
			if (Elysium::Core::Template::Net::Sockets::IPProtectionLevel::Unspecified == Level)
			{
				throw Elysium::Core::Template::Exceptions::ArgumentException(u8"Level");
			}

			switch (GetAddressFamily())
			{
			case Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetwork:
				SetSocketOption(Elysium::Core::Template::Net::Sockets::SocketOptionLevel::IP, Elysium::Core::Template::Net::Sockets::SocketOptionName::IPProtectionLevel,
					static_cast<Elysium::Core::Template::System::int32_t>(Level));
				break;
			case Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetworkV6:
				SetSocketOption(Elysium::Core::Template::Net::Sockets::SocketOptionLevel::IPv6, Elysium::Core::Template::Net::Sockets::SocketOptionName::IPProtectionLevel,
					static_cast<Elysium::Core::Template::System::int32_t>(Level));
				break;
			default:
				// @ToDo
				throw;
			}
		}

		inline void SetReceiveTimeout(const Elysium::Core::Template::System::int32_t Timeout)
		{
			SetSocketOption(Elysium::Core::Template::Net::Sockets::SocketOptionLevel::Socket, Elysium::Core::Template::Net::Sockets::SocketOptionName::ReceiveTimeout, Timeout);
		}

		inline void SetSendTimeout(const Elysium::Core::Template::System::int32_t Timeout)
		{
			SetSocketOption(Elysium::Core::Template::Net::Sockets::SocketOptionLevel::Socket, Elysium::Core::Template::Net::Sockets::SocketOptionName::SendTimeout, Timeout);
		}

		inline void SetReceiveBufferSize(const Elysium::Core::Template::System::int32_t BufferSize)
		{
			SetSocketOption(Elysium::Core::Template::Net::Sockets::SocketOptionLevel::Socket, Elysium::Core::Template::Net::Sockets::SocketOptionName::ReceiveBuffer, BufferSize);
		}

		inline void SetSendBufferSize(const Elysium::Core::Template::System::int32_t BufferSize)
		{
			SetSocketOption(Elysium::Core::Template::Net::Sockets::SocketOptionLevel::Socket, Elysium::Core::Template::Net::Sockets::SocketOptionName::SendBuffer, BufferSize);
		}

		inline void SetBlocking(const bool Value)
		{
			Elysium::Core::Template::Net::Sockets::SocketError Result = static_cast<Elysium::Core::Template::Net::Sockets::SocketError>(
				IOControl(Elysium::Core::Template::Net::Sockets::IOControlCode::NonBlockingIO, Value == true ? 0 : -1, nullptr, 0));
			if (Elysium::Core::Template::Net::Sockets::SocketError::Success != Result)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			_IsBlocking = Value;
		}
	public:
		inline const Elysium::Core::Template::System::int32_t IOControl(const Elysium::Core::Template::Net::Sockets::IOControlCode ControlCode,
			const Elysium::Core::Template::System::uint32_t OptionInValue, Elysium::Core::Template::System::byte* OptionOutValue, 
			const Elysium::Core::Template::System::size OptionOutValueLength)
		{
			// @ToDo
			throw;
			/*
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Bytes = BitConverter::GetBytes(OptionInValue);
			return IOControl(static_cast<const Elysium::Core::Template::System::int32_t>(ControlCode), &Bytes[0], Bytes.GetLength(), OptionOutValue, OptionOutValueLength);
			*/
		}

		inline const Elysium::Core::Template::System::int32_t IOControl(const Elysium::Core::Template::Net::Sockets::IOControlCode ControlCode,
			const Elysium::Core::Template::System::byte* OptionInValue, const Elysium::Core::Template::System::size OptionInValueLength,
			Elysium::Core::Template::System::byte* OptionOutValue, const Elysium::Core::Template::System::size OptionOutValueLength)
		{
			return IOControl(static_cast<const Elysium::Core::Template::System::int32_t>(ControlCode), OptionInValue, OptionInValueLength, OptionOutValue, OptionOutValueLength);
		}

		inline const Elysium::Core::Template::System::int32_t IOControl(const Elysium::Core::Template::System::int32_t ControlCode,
			const Elysium::Core::Template::System::byte* OptionInValue, const Elysium::Core::Template::System::size OptionInValueLength,
			Elysium::Core::Template::System::byte* OptionOutValue, const Elysium::Core::Template::System::size OptionOutValueLength)
		{
			unsigned long BytesReturned = 0;
			const int Result = WSAIoctl(_SocketHandle, ControlCode, reinterpret_cast<DWORD*>(&OptionInValue), OptionInValueLength,
				OptionOutValue, OptionOutValueLength, &BytesReturned, nullptr, nullptr);
			if(SOCKET_ERROR == Result)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			return Result;
		}

		inline const bool Poll(const Elysium::Core::Template::System::int32_t MicroSeconds, const Elysium::Core::Template::Net::Sockets::SelectMode Mode)
		{
			fd_set CheckSet{};
			FD_SET(_SocketHandle, &CheckSet);

			timeval Duration{};
			Duration.tv_sec = static_cast<Elysium::Core::Template::System::int32_t>(MicroSeconds / 1000000);
			Duration.tv_usec = static_cast<Elysium::Core::Template::System::int32_t>(MicroSeconds % 1000000);

			const int Result = select(0, Mode == Elysium::Core::Template::Net::Sockets::SelectMode::SelectRead ? &CheckSet : nullptr,
				Mode == Elysium::Core::Template::Net::Sockets::SelectMode::SelectWrite ? &CheckSet : nullptr,
				Mode == Elysium::Core::Template::Net::Sockets::SelectMode::SelectError ? &CheckSet : nullptr, &Duration);
			if (SOCKET_ERROR == Result)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			return FD_ISSET(_SocketHandle, &CheckSet);
		}
		/*
		inline const bool Poll(const Elysium::Core::TimeSpan Duration, const Elysium::Core::Template::Net::Sockets::SelectMode Mode)
		{
			return Poll(Duration.GetTotalMilliseconds() * 1000, Mode);
		}
		*/
	public:
		inline void Connect(const Elysium::Core::Template::Text::StringView<char8_t> Host, const Elysium::Core::Template::System::uint16_t Port)
		{
			// @ToDo: parse host to decide whether to use IpEndPoint or DnsEndPoint (can be done easily once I got regex working)
			DnsEndPoint RemoteEndPoint = DnsEndPoint(Host, Port, Elysium::Core::Template::Net::Sockets::AddressFamily::InterNetwork);
			Connect(RemoteEndPoint);
		}

		// @ToDo: concept for endpoints (currently only dnsendpoint ipendpoint)
		template <class T>
		inline void Connect(const T RemoteEndPoint)
		{
			if (_IsConnected)
			{
				return;
			}

			socklen_t SerializedAddressLength = 0;
			sockaddr_storage SerializedAddress = RemoteEndPoint.Serialize(SerializedAddressLength);
			sockaddr* Name = reinterpret_cast<sockaddr*>(&SerializedAddress);
			const int Result = connect(_SocketHandle, Name, SerializedAddressLength);
			if (SOCKET_ERROR == Result)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			_IsConnected = true;
		}

		template <class T>
		inline void Bind(const T LocalEndPoint)
		{
			socklen_t SerializedAddressLength = 0;
			sockaddr_storage SerializedAddress = LocalEndPoint.Serialize(SerializedAddressLength);
			sockaddr* Name = reinterpret_cast<sockaddr*>(&SerializedAddress);
			const int Result = bind(_SocketHandle, Name, SerializedAddressLength);
			if (SOCKET_ERROR == Result)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}
		}

		inline void Listen(const Elysium::Core::Template::System::int32_t Backlog)
		{
			const int Result = listen(_SocketHandle, Backlog);
			if (SOCKET_ERROR == Result)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}
		}

		inline Socket Accept()
		{
			SOCKET ClientWinSocketHandle{};
			sockaddr_in ConnectionInfo{};
			int AddressLength = sizeof(ConnectionInfo);

			ClientWinSocketHandle = accept(_SocketHandle, (sockaddr*)&ConnectionInfo, &AddressLength);
			if (INVALID_SOCKET == ClientWinSocketHandle)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			return Socket(ClientWinSocketHandle);
		}
	public:
		inline const Elysium::Core::Template::System::size Receive(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			WSABUF WSABuffer
			{
				.len = static_cast<unsigned long>(Count),
				.buf = reinterpret_cast<char*>(const_cast<Elysium::Core::Template::System::byte*>(Buffer))
			};

			DWORD BytesReceived = 0;
			DWORD Flags = 0;

			const int Result = WSARecv(_SocketHandle, &WSABuffer, 1, &BytesReceived, &Flags, nullptr, nullptr);
			if (SOCKET_ERROR == Result)
			{
				int ErrorCode = WSAGetLastError();
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException(ErrorCode);
			}

			return BytesReceived;
		}
		/*
		// @ToDo: concept for endpoints (currently only dnsendpoint ipendpoint)
		template <class T>
		inline const Elysium::Core::Template::System::size ReceiveFrom(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count,
			T& RemoteEndpoint)
		{
			throw;
		}

		// @ToDo: concept for endpoints (currently only dnsendpoint ipendpoint)
		template <class T>
		inline const Elysium::Core::Template::System::size ReceiveFrom(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count, 
			const SocketFlags SocketFlags, T& RemoteEndpoint)
		{
			throw;
		}
		*/
		inline const Elysium::Core::Template::System::size Send(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			const int BytesSent = send(_SocketHandle, reinterpret_cast<const char*>(&Buffer[0]), static_cast<const int>(Count), 0);
			if (SOCKET_ERROR == BytesSent)
			{
				int ErrorCode = WSAGetLastError();
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException(ErrorCode);
			}

			return BytesSent;
		}
		/*
		// @ToDo: concept for endpoints (currently only dnsendpoint ipendpoint)
		template <class T>
		inline const Elysium::Core::Template::System::size SendTo(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count,
			const T RemoteEndpoint)
		{
			throw;
		}

		// @ToDo: concept for endpoints (currently only dnsendpoint ipendpoint)
		template <class T>
		inline const Elysium::Core::Template::System::size SendTo(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count,
			const SocketFlags SocketFlags, const T RemoteEndpoint)
		{
			throw;
		}
		*/
	public:
		inline void Shutdown(const Elysium::Core::Template::Net::Sockets::SocketShutdown Value)
		{
			const int Result = shutdown(_SocketHandle, static_cast<int>(Value));
			if (SOCKET_ERROR == Result)
			{
				int ErrorCode = WSAGetLastError();
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException(ErrorCode);
			}
		}

		inline void Disconnect(const bool ReuseSocket)
		{
			if (!_IsConnected)
			{
				return;
			}

			//WSARecvDisconnect()
			//WSASendDisconnect()

			Shutdown(Elysium::Core::Template::Net::Sockets::SocketShutdown::Both);
			_IsConnected = false;
		}

		inline void Close()
		{
			if (INVALID_SOCKET == _SocketHandle)
			{
				return;
			}

			if (nullptr != _CompletionPortHandle)
			{
				CancelThreadpoolIo(_CompletionPortHandle);
				CloseThreadpoolIo(_CompletionPortHandle);

				_CompletionPortHandle = nullptr;
			}

			int CloseResult = closesocket(_SocketHandle);
			if (0 != CloseResult)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}
			_SocketHandle = INVALID_SOCKET;
			_IsClosed = true;
		}	
	public:
		inline static void Select(Elysium::Core::Template::Container::Vector<Socket*>* CheckRead, Elysium::Core::Template::Container::Vector<Socket*>* CheckWrite, 
			Elysium::Core::Template::Container::Vector<Socket*>* CheckError, const Elysium::Core::Template::System::uint32_t MicroSeconds)
		{
			fd_set ReadSet{};
			fd_set WriteSet{};
			fd_set ErrorSet{};

			if (nullptr != CheckRead)
			{
				for (Elysium::Core::Template::System::size i = 0; i < CheckRead->GetLength(); ++i)
				{
					FD_SET(CheckRead->operator[](i)->_SocketHandle, &ReadSet);
				}
			}
			if (nullptr != CheckWrite)
			{
				for (Elysium::Core::Template::System::size i = 0; i < CheckWrite->GetLength(); ++i)
				{
					FD_SET(CheckWrite->operator[](i)->_SocketHandle, &WriteSet);
				}
			}
			if (nullptr != CheckError)
			{
				for (Elysium::Core::Template::System::size i = 0; i < CheckError->GetLength(); ++i)
				{
					FD_SET(CheckError->operator[](i)->_SocketHandle, &ErrorSet);
				}
			}

			timeval Duration;
			Duration.tv_sec = static_cast<Elysium::Core::Template::System::int32_t>(MicroSeconds / 1000000);
			Duration.tv_usec = static_cast<Elysium::Core::Template::System::int32_t>(MicroSeconds % 1000000);
			const int SelectResult = select(0, &ReadSet, &WriteSet, &ErrorSet, &Duration);
			if (SOCKET_ERROR == SelectResult)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			if (nullptr != CheckRead)
			{
				for (Elysium::Core::Template::System::size i = CheckRead->GetLength(); i > 0; --i)
				{
					if (!FD_ISSET(CheckRead->operator[](i - 1)->_SocketHandle, &ReadSet))
					{
						CheckRead->EraseAt(i - 1);
					}
				}
			}
			if (nullptr != CheckWrite)
			{
				for (Elysium::Core::Template::System::size i = CheckWrite->GetLength(); i > 0; --i)
				{
					if (!FD_ISSET(CheckWrite->operator[](i - 1)->_SocketHandle, &WriteSet))
					{
						CheckWrite->EraseAt(i - 1);
					}
				}
			}
			if (nullptr != CheckError)
			{
				for (Elysium::Core::Template::System::size i = CheckError->GetLength(); i > 0; --i)
				{
					if (!FD_ISSET(CheckError->operator[](i - 1)->_SocketHandle, &ErrorSet))
					{
						CheckError->EraseAt(i - 1);
					}
				}
			}
		}
		/*
		inline static void Select(Elysium::Core::Template::Container::Vector<Socket*>* CheckRead, Elysium::Core::Template::Container::Vector<Socket*>* CheckWrite,
			Elysium::Core::Template::Container::Vector<Socket*>* CheckError, const Elysium::Core::TimeSpan Duration)
		{
			return Select(CheckRead, CheckWrite, CheckError, Duration.GetTotalMilliseconds() * 1000);
		}
		*/
	private:
		struct WindowsSocketLifetime
		{
		public:
			inline WindowsSocketLifetime()
			{
				static constexpr const int DesiredMajorVersion = 2;
				static constexpr const int DesiredMinorVersion = 2;

				WSADATA Data{};
				const int StartupResult = WSAStartup(MAKEWORD(DesiredMajorVersion, DesiredMinorVersion), &Data);
				if (0 != StartupResult)
				{
					throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
				}

				if (LOBYTE(Data.wVersion) != DesiredMajorVersion || HIBYTE(Data.wVersion) != DesiredMinorVersion)
				{
					WSACleanup();

					// winsocket has been initialized but not at the requested version
					// @ToDo: throw specific exception
					throw Elysium::Core::Template::Exceptions::Exception();
				}
			}

			inline ~WindowsSocketLifetime()
			{
				WSACleanup();
			}
		};
	private:
		inline SOCKET CreateWinSocket(const Elysium::Core::Template::Net::Sockets::AddressFamily AddressFamily, const Elysium::Core::Template::Net::Sockets::SocketType SocketType,
			const Elysium::Core::Template::Net::Sockets::ProtocolType ProtocolType)
		{
			// ensure WSAStartup
			static WindowsSocketLifetime Instance;

			return WSASocket(static_cast<Elysium::Core::Template::System::int32_t>(AddressFamily), static_cast<Elysium::Core::Template::System::int32_t>(SocketType), 
				static_cast<Elysium::Core::Template::System::int32_t>(ProtocolType), nullptr, 0, WSA_FLAG_OVERLAPPED);
		}

		inline LPFN_CONNECTEX RetrieveFunctionConnectEx(SOCKET SocketHandle)
		{
			if (INVALID_SOCKET == SocketHandle)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			DWORD BytesReturned = 0;
			GUID GuidConnectEx = WSAID_CONNECTEX;
			LPFN_CONNECTEX FunctionConnectEx;

			int ResultConnectEx = WSAIoctl(SocketHandle, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidConnectEx, sizeof(GuidConnectEx), &FunctionConnectEx,
				sizeof(FunctionConnectEx), &BytesReturned, nullptr, nullptr);
			if (SOCKET_ERROR == ResultConnectEx)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			return FunctionConnectEx;
		}

		inline LPFN_DISCONNECTEX RetrieveFunctionDisconnectEx(SOCKET SocketHandle)
		{
			if (INVALID_SOCKET == SocketHandle)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			DWORD BytesReturned = 0;
			GUID GuidDisconnectEx = WSAID_DISCONNECTEX;
			LPFN_DISCONNECTEX FunctionDisconnectEx;

			int ResultDisconnectEx = WSAIoctl(SocketHandle, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidDisconnectEx, sizeof(GuidDisconnectEx), &FunctionDisconnectEx,
				sizeof(FunctionDisconnectEx), &BytesReturned, nullptr, nullptr);
			if (SOCKET_ERROR == ResultDisconnectEx)
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}

			return FunctionDisconnectEx;
		}

		inline static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
		{	// @ToDo
			throw;
		}
	private:
		SOCKET _SocketHandle;
		PTP_IO _CompletionPortHandle;

		LPFN_CONNECTEX ConnectEx;
		LPFN_DISCONNECTEX DisconnectEx;

		bool _IsConnected;
		bool _IsClosed = false;
		bool _IsBlocking = true;
	};
#endif
}
#endif
