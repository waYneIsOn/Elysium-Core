#include "Socket.hpp"

#ifndef ELYSIUM_CORE_NET_FORMATCONVERTER
#include "FormatConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#include "SocketException.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_DNSENDPOINT
#include "DnsEndPoint.hpp"
#endif

Elysium::Core::Net::Sockets::Socket::Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _AddressFamily(AddressFamily), _SocketType(SocketType), _ProtocolType(ProtocolType),
	_WinSocketHandle(INVALID_SOCKET)
{
	InitializeWinSockAPI();
}
Elysium::Core::Net::Sockets::Socket::~Socket()
{
	Disconnect(true);
	WSACleanup();
}

const Elysium::Core::Net::Sockets::AddressFamily & Elysium::Core::Net::Sockets::Socket::GetAddressFamily() const
{
	return _AddressFamily;
}

const Elysium::Core::Net::Sockets::SocketType & Elysium::Core::Net::Sockets::Socket::GetSocketType() const
{
	return _SocketType;
}

const Elysium::Core::Net::Sockets::ProtocolType & Elysium::Core::Net::Sockets::Socket::GetProtocolType() const
{
	return _ProtocolType;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetAvailable() const
{
	char Buffer;
	Elysium::Core::int32_t BytesAvailable = recv(_WinSocketHandle, &Buffer, 1, MSG_PEEK);
	if (BytesAvailable == SOCKET_ERROR)
	{
		throw SocketException(u8"no bytes available.\r\n", WSAGetLastError());
	}

	return BytesAvailable;
}

const bool Elysium::Core::Net::Sockets::Socket::GetBlocking() const
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

const bool Elysium::Core::Net::Sockets::Socket::GetIsConnected() const
{
	return _IsConnected;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetReceiveTimeout() const
{
	Elysium::Core::int32_t Result;
	Elysium::Core::int32_t ResultLength = sizeof(Elysium::Core::int32_t);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetSendTimeout() const
{
	Elysium::Core::int32_t Result;
	Elysium::Core::int32_t ResultLength = sizeof(Elysium::Core::int32_t);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDTIMEO, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetReceiveBufferSize() const
{
	Elysium::Core::int32_t Result;
	Elysium::Core::int32_t ResultLength = sizeof(Elysium::Core::int32_t);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetSendBufferSize() const
{
	Elysium::Core::int32_t Result;
	Elysium::Core::int32_t ResultLength = sizeof(Elysium::Core::int32_t);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't get receive timeout.\r\n", WSAGetLastError());
	}
	return Result;
}

void Elysium::Core::Net::Sockets::Socket::SetReceiveTimeout(const Elysium::Core::int32_t Timeout)
{
	SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveTimeout, Timeout);
}
void Elysium::Core::Net::Sockets::Socket::SetSendTimeout(const Elysium::Core::int32_t Timeout)
{
	SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendTimeout, Timeout);
}
void Elysium::Core::Net::Sockets::Socket::SetReceiveBufferSize(const Elysium::Core::int32_t BufferSize)
{
	SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveBuffer, BufferSize);
}
void Elysium::Core::Net::Sockets::Socket::SetSendBufferSize(const Elysium::Core::int32_t BufferSize)
{
	SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendBuffer, BufferSize);
}

void Elysium::Core::Net::Sockets::Socket::Connect(const String& Host, const Elysium::Core::int32_t Port)
{
	DnsEndPoint RemoteEndPoint = DnsEndPoint(Host, Port, AddressFamily::InterNetwork);
	Connect(RemoteEndPoint);
}
void Elysium::Core::Net::Sockets::Socket::Connect(const EndPoint & RemoteEndPoint)
{
	//if ((_WinSocketHandle = socket(FormatConverter::Convert(_AddressFamily), FormatConverter::Convert(_SocketType), FormatConverter::Convert(_ProtocolType))) == INVALID_SOCKET)
	if ((_WinSocketHandle = WSASocket(FormatConverter::Convert(_AddressFamily), FormatConverter::Convert(_SocketType), FormatConverter::Convert(_ProtocolType), 0, 0, 0)) == INVALID_SOCKET)
	{
		throw SocketException(u8"An error occurred when attempting to access the socket.\r\n", WSAGetLastError());
	}
	/*
	else
	{
		// configurate the socket with the default settings
		SetReceiveBufferSize(65536);
		SetSendBufferSize(65536);
		SetReceiveTimeout(-1);
		SetSendTimeout(-1);
	}
	*/
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
	
	SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReuseAddress, true);	
	Shutdown(SocketShutdown::Both);
	if (!ReuseSocket)
	{
		Close();
	}

	_IsConnected = false;
}

void Elysium::Core::Net::Sockets::Socket::Bind(const EndPoint & LocalEndPoint)
{
	if ((_WinSocketHandle = socket(FormatConverter::Convert(_AddressFamily), FormatConverter::Convert(_SocketType), FormatConverter::Convert(_ProtocolType))) == INVALID_SOCKET)
	//if ((_WinSocketHandle = WSASocket(FormatConverter::Convert(_AddressFamily), FormatConverter::Convert(_SocketType), FormatConverter::Convert(_ProtocolType), 0, 0, 0)) == INVALID_SOCKET)
	{
		throw SocketException(u8"An error occurred when attempting to access the socket.\r\n", WSAGetLastError());
	}
	/*
	else
	{
		// configurate the socket with the default settings
		SetReceiveBufferSize(65536);
		SetSendBufferSize(65536);
		SetReceiveTimeout(-1);
		SetSendTimeout(-1);
	}
	*/
	const SocketAddress Address = LocalEndPoint.Serialize();
	if (Elysium::Core::int32_t Result = bind(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize()) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't bind socket.\r\n", WSAGetLastError());
	}
	else
	{
		// configurate the socket with the default settings
		SetReceiveBufferSize(65536);
		SetSendBufferSize(65536);
		//SetReceiveTimeout(-1);
		//SetSendTimeout(-1);
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

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::IOControl(const IOControlCode ControlCode, const Elysium::Core::byte * OptionInValue, const size_t OptionInValueLength, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength)
{
	throw 1;	// either BitConverter for unsigned integers isn't working correctly or I'm doing something else incorrectly
	/*
	unsigned long dwBytesReturned = 0;
	if (const Elysium::Core::int32_t Result = WSAIoctl(_WinSocketHandle, static_cast<const Elysium::Core::uint32_t>(ControlCode), &OptionInValue, OptionInValueLength,
		OptionOutValue, OptionOutValueLength, &dwBytesReturned, nullptr, nullptr) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't control the i/o mode of the socket.\r\n", WSAGetLastError());
	}
	else
	{
		return Result;
	}
	*/
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::IOControl(const IOControlCode ControlCode, const Elysium::Core::uint32_t OptionInValue, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength)
{
	unsigned long dwBytesReturned = 0;
	if (const Elysium::Core::int32_t Result = WSAIoctl(_WinSocketHandle, static_cast<const Elysium::Core::uint64_t>(ControlCode), (DWORD*)&OptionInValue, sizeof(const Elysium::Core::uint32_t),
		OptionOutValue, OptionOutValueLength, &dwBytesReturned, nullptr, nullptr) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't control the i/o mode of the socket.\r\n", WSAGetLastError());
	}
	else
	{
		return Result;
	}
}

void Elysium::Core::Net::Sockets::Socket::SetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const bool OptionValue)
{
	SetSocketOption(OptionLevel, OptionName, OptionValue == true ? 1 : 0);
}

void Elysium::Core::Net::Sockets::Socket::SetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const Elysium::Core::int32_t OptionValue)
{
	if (setsockopt(_WinSocketHandle, static_cast<Elysium::Core::int32_t>(OptionLevel), static_cast<Elysium::Core::int32_t>(OptionName),
		(char*)&OptionValue, sizeof(const Elysium::Core::int32_t)) == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't set socket option.\r\n", WSAGetLastError());
	}
}

const size_t Elysium::Core::Net::Sockets::Socket::Send(const Elysium::Core::byte * Buffer, const size_t Count) const
{
	Elysium::Core::int32_t BytesSent = send(_WinSocketHandle, (const char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count), 0);
	if (BytesSent == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't send bytes.\r\n", WSAGetLastError());
	}

	return BytesSent;
}

const size_t Elysium::Core::Net::Sockets::Socket::SendTo(const Elysium::Core::byte * Buffer, const size_t Count, const EndPoint & RemoteEndpoint) const
{
	return SendTo(Buffer, Count, SocketFlags::None, RemoteEndpoint);
}

const size_t Elysium::Core::Net::Sockets::Socket::SendTo(const Elysium::Core::byte * Buffer, const size_t Count, const SocketFlags SocketFlags, const EndPoint & RemoteEndpoint) const
{
	const SocketAddress Address = RemoteEndpoint.Serialize();
	Elysium::Core::int32_t BytesSent = sendto(_WinSocketHandle, (const char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count),
		static_cast<const Elysium::Core::int32_t>(SocketFlags), (const sockaddr*)&Address, Address.GetSize());
	if (BytesSent == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't send bytes.\r\n", WSAGetLastError());
	}

	return BytesSent;
}

const size_t Elysium::Core::Net::Sockets::Socket::Receive(Elysium::Core::byte * Buffer, const size_t Count) const
{
	Elysium::Core::int32_t BytesReceived = recv(_WinSocketHandle, (char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count), 0);
	if (BytesReceived == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't received bytes.\r\n", WSAGetLastError());
	}

	return BytesReceived;
}

const size_t Elysium::Core::Net::Sockets::Socket::ReceiveFrom(const Elysium::Core::byte * Buffer, const size_t Count, EndPoint & RemoteEndpoint) const
{
	return ReceiveFrom(Buffer, Count, SocketFlags::None, RemoteEndpoint);
}

const size_t Elysium::Core::Net::Sockets::Socket::ReceiveFrom(const Elysium::Core::byte * Buffer, const size_t Count, const SocketFlags SocketFlags, EndPoint & RemoteEndpoint) const
{
	SocketAddress Address = RemoteEndpoint.Serialize();
	Elysium::Core::int32_t AddressLength = Address.GetSize();
	/*
	sockaddr_in Address;
	Elysium::Core::int32_t AddressLength = sizeof(Address);
	*/
	Elysium::Core::int32_t BytesReceived = recvfrom(_WinSocketHandle, (char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count),
		static_cast<const Elysium::Core::int32_t>(SocketFlags), (sockaddr*)&Address, &AddressLength);
	if (BytesReceived == SOCKET_ERROR)
	{
		throw SocketException(u8"couldn't received bytes.\r\n", WSAGetLastError());
	}

	return BytesReceived;
}

void Elysium::Core::Net::Sockets::Socket::InitializeWinSockAPI()
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

Elysium::Core::Net::Sockets::Socket::Socket(SOCKET WinSocketHandle, AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _WinSocketHandle(WinSocketHandle),
	_AddressFamily(AddressFamily), _SocketType(SocketType), _ProtocolType(ProtocolType)
{ }
