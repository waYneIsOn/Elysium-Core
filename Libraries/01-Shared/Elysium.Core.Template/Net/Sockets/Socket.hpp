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

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_ADDRESSFAMILY
#include "AddressFamily.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_PROTOCOLTYPE
#include "ProtocolType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETOPTIONLEVEL
#include "SocketOptionLevel.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_NET_SOCKETS_SOCKETOPTIONNAME
#include "SocketOptionName.hpp"
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
			ConnectEx(RetrieveFunctionConnectEx(_SocketHandle)), DisconnectEx(RetrieveFunctionDisconnectEx(_SocketHandle))
		{ }
	public:
		inline constexpr Socket(const Elysium::Core::Template::Net::Sockets::AddressFamily AddressFamily, const Elysium::Core::Template::Net::Sockets::SocketType SocketType,
			const Elysium::Core::Template::Net::Sockets::ProtocolType ProtocolType)
			: _SocketHandle(CreateWinSocket(AddressFamily, SocketType, ProtocolType)), _CompletionPortHandle(CreateThreadpoolIo(reinterpret_cast<HANDLE>(_SocketHandle),
				&IOCompletionPortCallback, this, &Elysium::Core::Template::Threading::ThreadPool::GetIOPool()._Environment)),
			ConnectEx(RetrieveFunctionConnectEx(_SocketHandle)), DisconnectEx(RetrieveFunctionDisconnectEx(_SocketHandle))
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
			const Elysium::Core::Template::System::int32_t OptionLength)
		{
			Elysium::Core::Template::Container::Vector<Elysium::Core::Template::System::byte> Result(OptionLength);
			if (SOCKET_ERROR == getsockopt(_SocketHandle, static_cast<Elysium::Core::Template::System::int32_t>(OptionLevel),
				static_cast<Elysium::Core::Template::System::int32_t>(OptionName), reinterpret_cast<char*>(&Result[0]), const_cast<int*>(reinterpret_cast<const int*>(&OptionLength))))
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

		inline const Elysium::Core::Template::System::int32_t GetReceiveTimeout() const
		{
			//return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveTimeout, sizeof(Elysium::Core::Template::System::int32_t));

			Elysium::Core::Template::System::int32_t Result;
			Elysium::Core::Template::System::int32_t ResultLength = sizeof(Result);
			if (SOCKET_ERROR == getsockopt(_SocketHandle, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&Result), &ResultLength))
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}
			return Result;
		}

		inline const Elysium::Core::Template::System::int32_t GetSendTimeout() const
		{
			//return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendTimeout, sizeof(Elysium::Core::Template::System::int32_t));

			Elysium::Core::Template::System::int32_t Result;
			Elysium::Core::Template::System::int32_t ResultLength = sizeof(Result);
			if (SOCKET_ERROR == getsockopt(_SocketHandle, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char*>(&Result), &ResultLength))
			{
				throw Elysium::Core::Template::Exceptions::Net::Sockets::SocketException();
			}
			return Result;
		}
	public:
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
		}
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
	};
#endif
}
#endif
