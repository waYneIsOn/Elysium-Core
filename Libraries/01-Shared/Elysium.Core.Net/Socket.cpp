#include "Socket.hpp"

#ifndef ELYSIUM_CORE_NET_FORMATCONVERTER
#include "FormatConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#include "SocketException.hpp"
#endif

#ifndef _WS2TCPIP_H_
#include <Ws2tcpip.h>	// InetPton
#endif

#ifndef _INC_TCHAR
#include <Tchar.h>	// _T macro
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Net::Sockets::Socket::Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _AddressFamily(AddressFamily), _SocketType(SocketType), _ProtocolType(ProtocolType)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != SOCKET_ERROR)
	{
		if (LOBYTE(wsaData.wVersion) == 2 && HIBYTE(wsaData.wVersion) == 2)
		{
			if ((_WinSocketHandle = socket(FormatConverter::Convert(_AddressFamily), FormatConverter::Convert(_SocketType), FormatConverter::Convert(_ProtocolType))) == INVALID_SOCKET)
			{
				WSACleanup();
			}
			else
			{
				// configurate the socket with the default settings
				SetReceiveBufferSize(65536);
				SetSendBufferSize(65536);
				SetReceiveTimeout(0);
				SetSendTimeout(0);
			}
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

Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::Sockets::Socket::GetAddressFamily()
{
	return _AddressFamily;
}
Elysium::Core::Net::Sockets::SocketType Elysium::Core::Net::Sockets::Socket::GetSocketType()
{
	return _SocketType;
}
Elysium::Core::Net::Sockets::ProtocolType Elysium::Core::Net::Sockets::Socket::GetProtocolType()
{
	return _ProtocolType;
}

int Elysium::Core::Net::Sockets::Socket::GetAvailable()
{
	char Buffer;
	int BytesAvailable = recv(_WinSocketHandle, &Buffer, 1, MSG_PEEK);
	if (BytesAvailable == SOCKET_ERROR)
	{
		throw SocketException(L"no bytes available.\r\n", WSAGetLastError());
	}

	return BytesAvailable;
}
bool Elysium::Core::Net::Sockets::Socket::GetIsConnected()
{
	return _IsConnected;
}
int Elysium::Core::Net::Sockets::Socket::GetReceiveTimeout()
{
	int Result;
	int ResultLength = sizeof(int);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}
int Elysium::Core::Net::Sockets::Socket::GetSendTimeout()
{
	int Result;
	int ResultLength = sizeof(int);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDTIMEO, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}
int Elysium::Core::Net::Sockets::Socket::GetReceiveBufferSize()
{
	int Result;
	int ResultLength = sizeof(int);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}
int Elysium::Core::Net::Sockets::Socket::GetSendBufferSize()
{
	int Result;
	int ResultLength = sizeof(int);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}

void Elysium::Core::Net::Sockets::Socket::SetReceiveTimeout(int Timeout)
{
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&Timeout, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't set receive timeout.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::SetSendTimeout(int Timeout)
{
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDTIMEO, (char*)&Timeout, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't set send timeout.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::SetReceiveBufferSize(int BufferSize)
{
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&BufferSize, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't set receive buffer size.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::SetSendBufferSize(int BufferSize)
{
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&BufferSize, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't set send buffer size.\r\n", WSAGetLastError());
	}
}

void Elysium::Core::Net::Sockets::Socket::Connect(const string& Host, int Port)
{
	// prepare the socket address info
	sockaddr_in ConnectionInfo;
	ConnectionInfo.sin_family = FormatConverter::Convert(_AddressFamily);
	ConnectionInfo.sin_port = htons(Port);

	// convert and add the hostname
	// ToDo: find a better method! this one doesn't seem to work correctly (or maybe there's something wrong with some DNS-functionality)
	// for instance http://www.tutorialspoint.com" doesn't get "converted" to "93.184.220.42"
	InetPtonA(ConnectionInfo.sin_family, Host.c_str(), &ConnectionInfo.sin_addr.s_addr);
	/*
	addrinfo Hints;
	Hints.ai_family = AF_UNSPEC; // AF_INET6 to force version
	Hints.ai_socktype = SOCK_STREAM;

	int Status;
	addrinfo* Results;
	if ((Status = getaddrinfo(Host->c_str(), NULL, &Hints, &Results)) != 0)
	{
		//throw Exception(gai_strerror(Status));
	}

	addrinfo* Item;
	for (Item = Results; Item != nullptr; Item = Item->ai_next)
	{
		if (Item->ai_family == AF_INET)
		{	// IPv4
			sockaddr_in* ipv4 = (sockaddr_in*)Item->ai_addr;
			ConnectionInfo.sin_addr = ipv4->sin_addr;
		}
		else
		{	// IPv6
			/*
			sockaddr_in6* ipv6 = (sockaddr_in6*)Item->ai_addr;
			ConnectionInfo.sin_addr = ipv6->sin6_addr;
			*-/
			throw Exception("not implemented");
		}
	}
	freeaddrinfo(Results);
	*/
	// try to connect to the server
	if (connect(_WinSocketHandle, (SOCKADDR*)&ConnectionInfo, sizeof(ConnectionInfo)) == SOCKET_ERROR)
	{
		closesocket(_WinSocketHandle);
		throw SocketException(L"connection not possible.\r\n", WSAGetLastError());
	}

	// set the corresponding flag
	_IsConnected = true;
}
void Elysium::Core::Net::Sockets::Socket::Connect(const EndPoint & RemoteEndPoint)
{
	throw NotImplementedException();
}
void Elysium::Core::Net::Sockets::Socket::Disconnect(bool ReuseSocket)
{
	if (!_IsConnected)
	{
		return;
	}

	// define whether we want to reuse the socket or not
	if (setsockopt(_WinSocketHandle, SOL_SOCKET, SO_REUSEADDR, (char*)&ReuseSocket, sizeof(int)) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't set socket reuse.\r\n", WSAGetLastError());
	}

	// close the socket
	closesocket(_WinSocketHandle);

	// set the corresponding flag
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
		throw SocketException(L"couldn't bind socket.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::Listen(const int Backlog)
{
	if (int Result = listen(_WinSocketHandle, Backlog) == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't listen.\r\n", WSAGetLastError());
	}
}
void Elysium::Core::Net::Sockets::Socket::Accept(Socket * ConnectedClient)
{
	if (ConnectedClient == nullptr)
	{	// ToDo: throw a specific exception
		throw Exception(L"ArgumentNullException: ConnectedClient");
	}

	// wait for a client to connect
	SOCKET ClientWinSocketHandle;
	sockaddr_in ConnectionInfo;
	int AddressLength = sizeof(ConnectionInfo);
	if ((ClientWinSocketHandle = accept(_WinSocketHandle, (sockaddr*)&ConnectionInfo, &AddressLength)) == INVALID_SOCKET)
	{
		throw SocketException(L"couldn't accept connection.\r\n", WSAGetLastError());
	}

	// populate ConnectedClient (don't instantiate!!!!)
	ConnectedClient->_WinSocketHandle = ClientWinSocketHandle;
	ConnectedClient->_AddressFamily = FormatConverter::Convert(ConnectionInfo.sin_family);
	ConnectedClient->_SocketType = _SocketType;
	ConnectedClient->_ProtocolType = _ProtocolType;
}

int Elysium::Core::Net::Sockets::Socket::Send(const byte* Buffer, const int Offset, const int Count)
{
	int BytesSent = send(_WinSocketHandle, (const char*)&Buffer[Offset], Count, 0);
	if (BytesSent == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't send bytes.\r\n", WSAGetLastError());
	}

	return BytesSent;
}
int Elysium::Core::Net::Sockets::Socket::Receive(byte* Buffer, const int Offset, const int Count)
{
	int BytesReceived = recv(_WinSocketHandle, (char*)&Buffer[Offset], Count, 0);
	if (BytesReceived == SOCKET_ERROR)
	{
		throw SocketException(L"couldn't received bytes.\r\n", WSAGetLastError());
	}

	return BytesReceived;
}

Elysium::Core::Net::Sockets::Socket::Socket(SOCKET WinSocketHandle, AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _WinSocketHandle(WinSocketHandle),
	_AddressFamily(AddressFamily), _SocketType(SocketType), _ProtocolType(ProtocolType)
{
}
