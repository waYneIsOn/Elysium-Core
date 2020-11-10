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

#ifndef ELYSIUM_CORE_BITCONVERTER
#include "../Elysium.Core/BitConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Net::Sockets::Socket::Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _WinSocketHandle(INVALID_SOCKET),
	_CompletionPort(CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0))
{
	InitializeWinSockAPI();
	
	if ((_WinSocketHandle = WSASocket(FormatConverter::Convert(AddressFamily), FormatConverter::Convert(SocketType), FormatConverter::Convert(ProtocolType), nullptr, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		throw SocketException();
	}

	Elysium::Core::int32_t CompletionKey = 0;
	if (CreateIoCompletionPort((HANDLE)_WinSocketHandle, _CompletionPort, (DWORD)CompletionKey, 0) == nullptr)
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

Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Net::Sockets::Socket::GetSocketOption(const SocketOptionLevel OptionLevel,
	const SocketOptionName OptionName, const Elysium::Core::int32_t OptionLength)
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
	return _IsBlocking;
}

const bool Elysium::Core::Net::Sockets::Socket::GetIsConnected() const
{
	return _IsConnected;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::GetReceiveTimeout() const
{
	//return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveTimeout, sizeof(Elysium::Core::int32_t));

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
	//return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendTimeout, sizeof(Elysium::Core::int32_t));

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
	//return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveBuffer, sizeof(Elysium::Core::int32_t));

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
	//return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendBuffer, sizeof(Elysium::Core::int32_t));

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

void Elysium::Core::Net::Sockets::Socket::SetIPProtectionLevel(const IPProtectionLevel Level)
{
	if (Level == IPProtectionLevel::Unspecified)
	{	// ToDo: message
		throw ArgumentException();
	}

	switch (GetAddressFamily())
	{
	case AddressFamily::InterNetwork:
		SetSocketOption(SocketOptionLevel::IP, SocketOptionName::IPProtectionLevel, static_cast<Elysium::Core::int32_t>(Level));
		break;
	case AddressFamily::InterNetworkV6:
		SetSocketOption(SocketOptionLevel::IPv6, SocketOptionName::IPProtectionLevel, static_cast<Elysium::Core::int32_t>(Level));
		break;
	default:
		// ToDo: message
		throw NotSupportedException();
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

void Elysium::Core::Net::Sockets::Socket::SetBlocking(const bool Value)
{
	SocketError Result = static_cast<SocketError>(IOControl(IOControlCode::NonBlockingIO, Value == true ? 0 : -1, nullptr, 0));
	if (Result != SocketError::Success)
	{
		throw SocketException();
	}

	_IsBlocking = Value;
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::IOControl(const IOControlCode ControlCode, const Elysium::Core::uint32_t OptionInValue, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength)
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = BitConverter::GetBytes(OptionInValue);
	return IOControl(static_cast<const Elysium::Core::int32_t>(ControlCode), &Bytes[0], Bytes.GetLength(), OptionOutValue, OptionOutValueLength);
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::IOControl(const IOControlCode ControlCode, const Elysium::Core::byte * OptionInValue, const size_t OptionInValueLength, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength)
{
	return IOControl(static_cast<const Elysium::Core::int32_t>(ControlCode), OptionInValue, OptionInValueLength, OptionOutValue, OptionOutValueLength);
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::IOControl(const Elysium::Core::int32_t ControlCode, const Elysium::Core::byte * OptionInValue, const size_t OptionInValueLength, Elysium::Core::byte * OptionOutValue, const size_t OptionOutValueLength)
{
	unsigned long BytesReturned = 0;
	if (const Elysium::Core::int32_t Result = WSAIoctl(_WinSocketHandle, ControlCode, (DWORD*)&OptionInValue, OptionInValueLength,
		OptionOutValue, OptionOutValueLength, &BytesReturned, nullptr, nullptr) == SOCKET_ERROR)
	{
		throw SocketException();
	}
	else
	{
		return Result;
	}
}

void Elysium::Core::Net::Sockets::Socket::Select(Elysium::Core::Collections::Template::List<const Socket*>* CheckRead, Elysium::Core::Collections::Template::List<const Socket*>* CheckWrite, Elysium::Core::Collections::Template::List<const Socket*>* CheckError, const Elysium::Core::int32_t MicroSeconds)
{
	fd_set ReadSet = fd_set();
	fd_set WriteSet = fd_set();
	fd_set ErrorSet = fd_set();

	FD_ZERO(&ReadSet);
	FD_ZERO(&WriteSet);
	FD_ZERO(&ErrorSet);

	if (CheckRead != nullptr)
	{
		for (size_t i = 0; i < CheckRead->GetCount(); i++)
		{
			FD_SET(CheckRead->operator[](i)->_WinSocketHandle, &ReadSet);
		}
	}
	if (CheckWrite != nullptr)
	{
		for (size_t i = 0; i < CheckWrite->GetCount(); i++)
		{
			FD_SET(CheckWrite->operator[](i)->_WinSocketHandle, &WriteSet);
		}
	}
	if (CheckError != nullptr)
	{
		for (size_t i = 0; i < CheckError->GetCount(); i++)
		{
			FD_SET(CheckError->operator[](i)->_WinSocketHandle, &ErrorSet);
		}
	}

	timeval Duration;
	Duration.tv_sec = static_cast<Elysium::Core::int32_t>(MicroSeconds / 1000000);
	Duration.tv_usec = static_cast<Elysium::Core::int32_t>(MicroSeconds % 1000000);

	if (const Elysium::Core::int32_t Result = select(0, &ReadSet, &WriteSet, &ErrorSet, &Duration) == SOCKET_ERROR)
	{
		throw SocketException();
	}

	if (CheckRead != nullptr)
	{
		for (size_t i = CheckRead->GetCount(); i > 0; i--)
		{
			if (!FD_ISSET(CheckRead->operator[](i - 1)->_WinSocketHandle, &ReadSet))
			{
				CheckRead->RemoveAt(i - 1);
			}
		}
	}
	if (CheckWrite != nullptr)
	{
		for (size_t i = CheckWrite->GetCount(); i > 0; i--)
		{
			if (!FD_ISSET(CheckWrite->operator[](i - 1)->_WinSocketHandle, &WriteSet))
			{
				CheckWrite->RemoveAt(i - 1);
			}
		}
	}
	if (CheckError != nullptr)
	{
		for (size_t i = CheckError->GetCount(); i > 0; i--)
		{
			if (!FD_ISSET(CheckError->operator[](i - 1)->_WinSocketHandle, &ErrorSet))
			{
				CheckError->RemoveAt(i - 1);
			}
		}
	}
}

void Elysium::Core::Net::Sockets::Socket::Select(Elysium::Core::Collections::Template::List<const Socket*>* CheckRead, Elysium::Core::Collections::Template::List<const Socket*>* CheckWrite, Elysium::Core::Collections::Template::List<const Socket*>* CheckError, const Elysium::Core::TimeSpan Duration)
{
	return Select(CheckRead, CheckWrite, CheckError, Duration.GetTotalMilliseconds() * 1000);
}

const bool Elysium::Core::Net::Sockets::Socket::Poll(const Elysium::Core::int32_t MicroSeconds, const SelectMode Mode)
{
	fd_set CheckSet = fd_set();
	FD_ZERO(&CheckSet);
	FD_SET(_WinSocketHandle, &CheckSet);

	timeval Duration;
	Duration.tv_sec = static_cast<Elysium::Core::int32_t>(MicroSeconds / 1000000);
	Duration.tv_usec = static_cast<Elysium::Core::int32_t>(MicroSeconds % 1000000);

	if (const Elysium::Core::int32_t Result = select(0, Mode == SelectMode::SelectRead ? &CheckSet : nullptr, Mode == SelectMode::SelectWrite ? &CheckSet : nullptr,
		Mode == SelectMode::SelectError ? &CheckSet : nullptr, &Duration) == SOCKET_ERROR)
	{
		throw SocketException();
	}

	return FD_ISSET(_WinSocketHandle, &CheckSet);
}

const bool Elysium::Core::Net::Sockets::Socket::Poll(const Elysium::Core::TimeSpan Duration, const SelectMode Mode)
{
	return Poll(Duration.GetTotalMilliseconds() * 1000, Mode);
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
		//Close();
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

const size_t Elysium::Core::Net::Sockets::Socket::Receive(const Elysium::Core::byte * Buffer, const size_t Count) const
{
	WSABUF WSABuffer = WSABUF();
	WSABuffer.len = Count;
	WSABuffer.buf = (char*)Buffer;

	Elysium::Core::int32_t BytesReceived = 0;

	SocketFlags Flags = SocketFlags::None;

	if (Elysium::Core::int32_t Result = WSARecv(_WinSocketHandle, (LPWSABUF)&WSABuffer, 1, (LPDWORD)&BytesReceived, (LPDWORD)&Flags, nullptr, nullptr) == SOCKET_ERROR)
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

const Elysium::Core::Net::Sockets::SendReceiveAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginReceive(const Elysium::Core::byte * Buffer, const size_t Count, 
	const size_t Size, SocketFlags Flags, const Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void * State) const
{
	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(this, Callback, State, 8192);

	WSABUF WSABuffer = WSABUF();
	WSABuffer.len = Count;
	WSABuffer.buf = (char*)Buffer;

	Elysium::Core::int32_t BytesReceived = 0;

	OVERLAPPED* Overlapped = new OVERLAPPED();
	Overlapped->Pointer = AsyncResult;

	Elysium::Core::int32_t Result = WSARecv(_WinSocketHandle, (LPWSABUF)&WSABuffer, 1,(LPDWORD)&BytesReceived, (LPDWORD)&Flags, Overlapped, nullptr);
	if (Result == SOCKET_ERROR)
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			throw SocketException();
		}
	}
	
	return AsyncResult;
}

const size_t Elysium::Core::Net::Sockets::Socket::EndReceive(const Elysium::Core::IAsyncResult * Result, Elysium::Core::Net::Sockets::SocketError & ErrorCode) const
{
	delete Result;

	return 0;
}

Elysium::Core::Net::Sockets::Socket::Socket(SOCKET WinSocketHandle)
	: _WinSocketHandle(WinSocketHandle)
{ 
	InitializeWinSockAPI();
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
