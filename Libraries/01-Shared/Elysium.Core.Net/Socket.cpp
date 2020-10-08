#include "Socket.hpp"

#ifndef ELYSIUM_CORE_NET_FORMATCONVERTER
#include "FormatConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_CONVERT
#include "../Elysium.Core/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef _WS2TCPIP_H_
#include <Ws2tcpip.h>	// InetPton
#endif

#ifndef _UCHAR
#include <uchar.h>
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#include "SocketException.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_DNSENDPOINT
#include "DnsEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Net::Sockets::Socket::Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _AddressFamily(AddressFamily), _SocketType(SocketType), _ProtocolType(ProtocolType),
	_WinSocketHandle(INVALID_SOCKET)
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
			WSACleanup();
		}
	}
}
Elysium::Core::Net::Sockets::Socket::~Socket()
{
	Disconnect(true);
	WSACleanup();
}

Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::Sockets::Socket::GetAddressFamily() const
{
	return _AddressFamily;
}
Elysium::Core::Net::Sockets::SocketType Elysium::Core::Net::Sockets::Socket::GetSocketType() const
{
	return _SocketType;
}
Elysium::Core::Net::Sockets::ProtocolType Elysium::Core::Net::Sockets::Socket::GetProtocolType() const
{
	return _ProtocolType;
}

int Elysium::Core::Net::Sockets::Socket::GetAvailable() const
{
	char Buffer;
	int BytesAvailable = recv(_WinSocketHandle, &Buffer, 1, MSG_PEEK);
	if (BytesAvailable == SOCKET_ERROR)
	{
		throw SocketException(u8"no bytes available.\r\n", WSAGetLastError());
	}

	return BytesAvailable;
}
bool Elysium::Core::Net::Sockets::Socket::GetBlocking() const
{	// ToDo: ioctlsocket seems to only be used for setting values?
	unsigned long Bla;
	if (ioctlsocket(_WinSocketHandle, FIONBIO, &Bla) == SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Elysium::Core::Net::Sockets::Socket::GetIsConnected() const
{
	return _IsConnected;
}
int Elysium::Core::Net::Sockets::Socket::GetReceiveTimeout() const
{
	int Result;
	int ResultLength = sizeof(int);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}
int Elysium::Core::Net::Sockets::Socket::GetSendTimeout() const
{
	int Result;
	int ResultLength = sizeof(int);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDTIMEO, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}
int Elysium::Core::Net::Sockets::Socket::GetReceiveBufferSize() const
{
	int Result;
	int ResultLength = sizeof(int);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}
int Elysium::Core::Net::Sockets::Socket::GetSendBufferSize() const
{
	int Result;
	int ResultLength = sizeof(int);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}

void Elysium::Core::Net::Sockets::Socket::SetReceiveTimeout(int Timeout)
{
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&Timeout, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't set receive timeout.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::SetSendTimeout(int Timeout)
{
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDTIMEO, (char*)&Timeout, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't set send timeout.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::SetReceiveBufferSize(int BufferSize)
{
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&BufferSize, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't set receive buffer size.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::SetSendBufferSize(int BufferSize)
{
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&BufferSize, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't set send buffer size.\r\n", WSAGetLastError());
	}
}

void Elysium::Core::Net::Sockets::Socket::Connect(const String& Host, const Elysium::Core::int32_t Port)
{
	DnsEndPoint RemoteEndPoint = DnsEndPoint(Host, Port, AddressFamily::InterNetwork);
	Connect(RemoteEndPoint);
}
void Elysium::Core::Net::Sockets::Socket::Connect(const EndPoint & RemoteEndPoint)
{
	if ((_WinSocketHandle = socket(FormatConverter::Convert(_AddressFamily), FormatConverter::Convert(_SocketType), FormatConverter::Convert(_ProtocolType))) == INVALID_SOCKET)
	{
		throw SocketException(u8"An error occurred when attempting to access the socket.\r\n", WSAGetLastError());
	}
	else
	{
		// configurate the socket with the default settings
		SetReceiveBufferSize(65536);
		SetSendBufferSize(65536);
		//SetReceiveTimeout(-1);
		//SetSendTimeout(-1);
	}

	const SocketAddress Address = RemoteEndPoint.Serialize();
	
	if (Elysium::Core::int32_t Result = connect(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize()) == SOCKET_ERROR)
	{
		Close();
		throw SocketException(u8"connection not possible.\r\n", WSAGetLastError());
	}

	_IsConnected = true;
}
void Elysium::Core::Net::Sockets::Socket::Close()
{
	closesocket(_WinSocketHandle);
	_WinSocketHandle = INVALID_SOCKET;
}
void Elysium::Core::Net::Sockets::Socket::Shutdown(const SocketShutdown Value)
{
	if (Elysium::Core::int32_t Result = shutdown(_WinSocketHandle, static_cast<Elysium::Core::int32_t>(Value)) == SOCKET_ERROR)
	{
		throw SocketException(u8"An error occurred when attempting to access the socket.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::Disconnect(const bool ReuseSocket)
{
	if (!_IsConnected)
	{
		return;
	}
	
	// define whether we want to reuse the socket or not
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_REUSEADDR, (char*)&ReuseSocket, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't set socket reuse.\r\n", WSAGetLastError());
	}
	
	Shutdown(SocketShutdown::Both);
	if (!ReuseSocket)
	{
		Close();
	}

	_IsConnected = false;
}

void Elysium::Core::Net::Sockets::Socket::Bind(const EndPoint & LocalEndPoint)
{
	/*
	SocketAddress Address;
	LocalEndPoint.Serialize(&Address);
	
	sockaddr_in ConnectionInfo;
	ConnectionInfo.sin_family = FormatConverter::Convert(Address.GetFamily());
	ConnectionInfo.sin_port = htons(Address.GetPort());	// ToDo: is it really necessary to call htons?
	*/
	
	
	// ToDo: use values from LocalEndPoint
	sockaddr_in ConnectionInfo;
	ConnectionInfo.sin_family = AF_INET;
	ConnectionInfo.sin_port = htons(27015);
	//InetPtonA(AF_INET, "127.0.0.1", &ConnectionInfo.sin_addr.s_addr);
	InetPtonA(AF_INET, "0.0.0.0", &ConnectionInfo.sin_addr.s_addr);

	if (int Result = bind(_WinSocketHandle, (SOCKADDR*)&ConnectionInfo, sizeof(ConnectionInfo)) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't bind socket.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::Listen(const int Backlog)
{
	if (int Result = listen(_WinSocketHandle, Backlog) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't listen.\r\n", WSAGetLastError());
	}
}
const Elysium::Core::Net::Sockets::Socket Elysium::Core::Net::Sockets::Socket::Accept()
{
	// wait for a client to connect
	SOCKET ClientWinSocketHandle;
	sockaddr_in ConnectionInfo;
	int AddressLength = sizeof(ConnectionInfo);
	if ((ClientWinSocketHandle = accept(_WinSocketHandle, (sockaddr*)&ConnectionInfo, &AddressLength)) == INVALID_SOCKET)
	{
		throw SocketException(u8"couldn't accept connection.\r\n", WSAGetLastError());
	}

	return Socket(ClientWinSocketHandle, _AddressFamily, _SocketType, _ProtocolType);
}

size_t Elysium::Core::Net::Sockets::Socket::Send(const byte* Buffer, const size_t Count) const
{
	int BytesSent = send(_WinSocketHandle, (const char*)&Buffer[0], (int)Count, 0);
	if (BytesSent == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't send bytes.\r\n", WSAGetLastError());
	}

	return (size_t)BytesSent;
}
size_t Elysium::Core::Net::Sockets::Socket::Receive(byte* Buffer, const size_t Count) const
{
	int BytesReceived = recv(_WinSocketHandle, (char*)&Buffer[0], (int)Count, 0);
	if (BytesReceived == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't received bytes.\r\n", WSAGetLastError());
	}

	return (size_t)BytesReceived;
}

Elysium::Core::Net::Sockets::Socket::Socket(SOCKET WinSocketHandle, AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _WinSocketHandle(WinSocketHandle),
	_AddressFamily(AddressFamily), _SocketType(SocketType), _ProtocolType(ProtocolType)
{ }
