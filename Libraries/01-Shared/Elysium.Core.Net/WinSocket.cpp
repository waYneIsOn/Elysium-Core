#include "WinSocket.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#include "SocketException.hpp"
#endif

void Elysium::Core::Net::Sockets::Internal::WinSocket::Initialize()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != SOCKET_ERROR)
	{
		if (LOBYTE(wsaData.wVersion) == 2 && HIBYTE(wsaData.wVersion) == 2)
		{
			// ...
		}
		else
		{
			// ToDo: I might obviously not be dealing with an error here but with an older api version. ergo I will have to deal with it at some point
			//Elysium::Core::int32_t ErrorCode = WSAGetLastError();
			Shutdown();
		}
	}
}

void Elysium::Core::Net::Sockets::Internal::WinSocket::Shutdown()
{
	WSACleanup();
}

LPFN_CONNECTEX Elysium::Core::Net::Sockets::Internal::WinSocket::RetrieveFunctionConnectEx(SOCKET NativeWinSocketHandle)
{
	if (NativeWinSocketHandle == INVALID_SOCKET)
	{
		throw SocketException();
	}

	DWORD BytesReturned = 0;
	GUID GuidConnectEx = WSAID_CONNECTEX;
	LPFN_CONNECTEX FunctionConnectEx;

	Elysium::Core::int32_t ResultConnectEx = WSAIoctl(NativeWinSocketHandle, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidConnectEx, sizeof(GuidConnectEx),
		&FunctionConnectEx, sizeof(FunctionConnectEx), &BytesReturned, nullptr, nullptr);
	if (ResultConnectEx == SOCKET_ERROR)
	{
		throw SocketException();
	}

	return FunctionConnectEx;
}

LPFN_DISCONNECTEX Elysium::Core::Net::Sockets::Internal::WinSocket::RetrieveFunctionDisconnectEx(SOCKET NativeWinSocketHandle)
{
	if (NativeWinSocketHandle == INVALID_SOCKET)
	{
		throw SocketException();
	}

	DWORD BytesReturned = 0;
	GUID GuidDisconnectEx = WSAID_DISCONNECTEX;
	LPFN_DISCONNECTEX FunctionDisconnectEx;

	Elysium::Core::int32_t ResultDisconnectEx = WSAIoctl(NativeWinSocketHandle, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidDisconnectEx, sizeof(GuidDisconnectEx),
		&FunctionDisconnectEx, sizeof(FunctionDisconnectEx), &BytesReturned, nullptr, nullptr);
	if (ResultDisconnectEx == SOCKET_ERROR)
	{
		throw SocketException();
	}

	return FunctionDisconnectEx;
}
/*
void Elysium::Core::Net::Sockets::Internal::WinSocket::NotifyIncomingWork(SOCKET NativeWinSocketHandle)
{
	StartThreadpoolIo((PTP_IO)NativeWinSocketHandle);
}

void Elysium::Core::Net::Sockets::Internal::WinSocket::CancelIncomingWorkNotification(SOCKET NativeWinSocketHandle)
{
	CancelThreadpoolIo((PTP_IO)NativeWinSocketHandle);
}
*/
#endif
