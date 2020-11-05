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

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Net::Sockets::Socket::Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _WinSocketHandle(INVALID_SOCKET)
{
	InitializeWinSockAPI();

	if ((_WinSocketHandle = socket(FormatConverter::Convert(AddressFamily), FormatConverter::Convert(SocketType), FormatConverter::Convert(ProtocolType))) == INVALID_SOCKET)
	{
		throw SocketException();
	}

}
Elysium::Core::Net::Sockets::Socket::Socket(Socket && Right)
{
	*this = std::move(Right);
}
Elysium::Core::Net::Sockets::Socket::~Socket()
{
	if (_WinSocketHandle != INVALID_SOCKET)
	{
		// ToDo: this needs to be handled correctly (only close after we've received the "current message", blocking/non-blocking etc.)
		Close();
	}
	WSACleanup();
}

Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::Socket::operator=(Socket && Right) noexcept
{
	if (this != &Right)
	{
		_WinSocketHandle = Right._WinSocketHandle;

		Right._WinSocketHandle = INVALID_SOCKET;
	}
	return *this;
}

const Elysium::Core::Net::Sockets::AddressFamily & Elysium::Core::Net::Sockets::Socket::GetAddressFamily() const
{
	WSAPROTOCOL_INFO proto;
	WSADuplicateSocket(_WinSocketHandle, GetCurrentProcessId(), &proto);
	return static_cast<Elysium::Core::Net::Sockets::AddressFamily>(proto.iAddressFamily);
}

const Elysium::Core::Net::Sockets::SocketType & Elysium::Core::Net::Sockets::Socket::GetSocketType() const
{
	WSAPROTOCOL_INFO proto;
	WSADuplicateSocket(_WinSocketHandle, GetCurrentProcessId(), &proto);
	return static_cast<Elysium::Core::Net::Sockets::SocketType>(proto.iSocketType);
}

const Elysium::Core::Net::Sockets::ProtocolType & Elysium::Core::Net::Sockets::Socket::GetProtocolType() const
{
	WSAPROTOCOL_INFO proto;
	WSADuplicateSocket(_WinSocketHandle, GetCurrentProcessId(), &proto);
	return static_cast<Elysium::Core::Net::Sockets::ProtocolType>(proto.iProtocol);
}

Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Net::Sockets::Socket::GetSocketOption(const SocketOptionLevel OptionLevel, const SocketOptionName OptionName, const Elysium::Core::int32_t OptionLength)
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Result = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(OptionLength);

	if (getsockopt(_WinSocketHandle, static_cast<Elysium::Core::int32_t>(OptionLevel), static_cast<Elysium::Core::int32_t>(OptionName),
		(char*)&Result[0], (int*)&OptionLength) == SOCKET_ERROR)
	{
		throw SocketException();
	}
	
	return Result;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetAvailable() const
{
	char Buffer;
	Elysium::Core::int32_t BytesAvailable = recv(_WinSocketHandle, &Buffer, 1, MSG_PEEK);
	if (BytesAvailable == SOCKET_ERROR)
	{
		throw SocketException();
	}

	return BytesAvailable;
}

const bool Elysium::Core::Net::Sockets::Socket::GetBlocking() const
{	
	//GetSocketOption(SocketOptionLevel::IP, SocketOptionName::BlockSource, 
	
	// ToDo: ioctlsocket seems to only be used for setting values?
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
		throw SocketException();
	}
	return Result;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetSendTimeout() const
{
	Elysium::Core::int32_t Result;
	Elysium::Core::int32_t ResultLength = sizeof(Elysium::Core::int32_t);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDTIMEO, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException();
	}
	return Result;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetReceiveBufferSize() const
{
	Elysium::Core::int32_t Result;
	Elysium::Core::int32_t ResultLength = sizeof(Elysium::Core::int32_t);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException();
	}
	return Result;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetSendBufferSize() const
{
	Elysium::Core::int32_t Result;
	Elysium::Core::int32_t ResultLength = sizeof(Elysium::Core::int32_t);
	if (getsockopt(_WinSocketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&Result, &ResultLength) == SOCKET_ERROR)
	{
		throw SocketException();
	}
	return Result;
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
		throw SocketException();
	}
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
	/*
	if (GetIsConnected())
	{
		return;
	}
	*/
	const SocketAddress Address = RemoteEndPoint.Serialize();
	Elysium::Core::int32_t Result;
	if ((Result = connect(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize())) == SOCKET_ERROR)
	{
		Close();
		throw SocketException();
	}

	_IsConnected = true;
}

void Elysium::Core::Net::Sockets::Socket::Shutdown(const SocketShutdown Value)
{
	Elysium::Core::int32_t Result;
	if ((Result = shutdown(_WinSocketHandle, static_cast<Elysium::Core::int32_t>(Value))) == SOCKET_ERROR)
	{
		throw SocketException();
	}
}

void Elysium::Core::Net::Sockets::Socket::Disconnect(const bool ReuseSocket)
{
	/*
	if (!GetIsConnected())
	{
		return;
	}
	*/
	/*
	SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReuseAddress, true);	
	Shutdown(SocketShutdown::Both);
	if (!ReuseSocket)
	{
		Close();
	}
	*/
	_IsConnected = false;
}

void Elysium::Core::Net::Sockets::Socket::Close()
{
	if (_IsClosed)
	{
		return;
	}

	closesocket(_WinSocketHandle);
	_WinSocketHandle = INVALID_SOCKET;
	_IsClosed = true;
}

void Elysium::Core::Net::Sockets::Socket::Bind(const EndPoint & LocalEndPoint)
{
	const SocketAddress Address = LocalEndPoint.Serialize();
	if (Elysium::Core::int32_t Result = bind(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize()) == SOCKET_ERROR)
	{
		throw SocketException();
	}
}

void Elysium::Core::Net::Sockets::Socket::Listen(const Elysium::Core::int32_t Backlog)
{
	if (int Result = listen(_WinSocketHandle, Backlog) == SOCKET_ERROR)
	{
		throw SocketException();
	}
}
const Elysium::Core::Net::Sockets::Socket Elysium::Core::Net::Sockets::Socket::Accept()
{
	SOCKET ClientWinSocketHandle;
	sockaddr_in ConnectionInfo;
	int AddressLength = sizeof(ConnectionInfo);
	if ((ClientWinSocketHandle = accept(_WinSocketHandle, (sockaddr*)&ConnectionInfo, &AddressLength)) == INVALID_SOCKET)
	{
		throw SocketException();
	}

	return Socket(ClientWinSocketHandle);
}

const Elysium::Core::IAsyncResult & Elysium::Core::Net::Sockets::Socket::BeginAccept(const Socket & AcceptSocket, Elysium::Core::uint16_t ReceiveSize, const Delegate<void, IAsyncResult&>& Callback, const void * State)
{
	//WSAEventSelect(_WinSocketHandle, )
	throw 1;
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
		throw SocketException();
	}
	else
	{
		return Result;
	}
}

const size_t Elysium::Core::Net::Sockets::Socket::Send(const Elysium::Core::byte * Buffer, const size_t Count) const
{
	Elysium::Core::int32_t BytesSent = send(_WinSocketHandle, (const char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count), 0);
	if (BytesSent == SOCKET_ERROR)
	{
		throw SocketException();
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
		throw SocketException();
	}

	return BytesSent;
}

const size_t Elysium::Core::Net::Sockets::Socket::Receive(Elysium::Core::byte * Buffer, const size_t Count) const
{
	Elysium::Core::int32_t BytesReceived = recv(_WinSocketHandle, (char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count), 0);
	if (BytesReceived == SOCKET_ERROR)
	{
		throw SocketException();
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
		throw SocketException();
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

Elysium::Core::Net::Sockets::Socket::Socket(SOCKET WinSocketHandle)
	: _WinSocketHandle(WinSocketHandle)
{ 
	InitializeWinSockAPI();
}
