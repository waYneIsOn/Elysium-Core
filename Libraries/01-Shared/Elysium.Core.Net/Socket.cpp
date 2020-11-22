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

#ifndef ELYSIUM_CORE_NET_IPENDPOINT
#include "IPEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_BITCONVERTER
#include "../Elysium.Core/BitConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../Elysium.Core.Threading/ThreadPool.hpp"
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
	: _WinSocketHandle(INVALID_SOCKET), _CompletionPortHandle(nullptr), ConnectEx(nullptr), DisconnectEx(nullptr)
{
	InitializeWinSockAPI();
	
	if ((_WinSocketHandle = WSASocket(FormatConverter::Convert(AddressFamily), FormatConverter::Convert(SocketType), FormatConverter::Convert(ProtocolType), nullptr, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		WSACleanup();
		throw SocketException();
	}

	_CompletionPortHandle = CreateThreadpoolIo((HANDLE)_WinSocketHandle, (PTP_WIN32_IO_CALLBACK)&IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::_IOPool._Environment);
	RetrieveFunctions();
}
Elysium::Core::Net::Sockets::Socket::Socket(Socket && Right)
{
	*this = std::move(Right);
}
Elysium::Core::Net::Sockets::Socket::~Socket()
{
	if (_CompletionPortHandle != nullptr)
	{
		CancelThreadpoolIo(_CompletionPortHandle);
		WaitForThreadpoolIoCallbacks(_CompletionPortHandle, false);
		CloseThreadpoolIo(_CompletionPortHandle);

		_CompletionPortHandle = nullptr;
	}

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

void Elysium::Core::Net::Sockets::Socket::Connect(const Elysium::Core::Net::EndPoint & RemoteEndPoint)
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
	//WSARecvDisconnect()
	//WSASendDisconnect()
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

void Elysium::Core::Net::Sockets::Socket::Bind(const Elysium::Core::Net::EndPoint & LocalEndPoint)
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
Elysium::Core::Net::Sockets::Socket Elysium::Core::Net::Sockets::Socket::Accept()
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

const size_t Elysium::Core::Net::Sockets::Socket::Receive(const Elysium::Core::byte * Buffer, const size_t Count)
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

const size_t Elysium::Core::Net::Sockets::Socket::ReceiveFrom(const Elysium::Core::byte * Buffer, const size_t Count, EndPoint & RemoteEndpoint)
{
	return ReceiveFrom(Buffer, Count, SocketFlags::None, RemoteEndpoint);
}

const size_t Elysium::Core::Net::Sockets::Socket::ReceiveFrom(const Elysium::Core::byte * Buffer, const size_t Count, const SocketFlags SocketFlags, EndPoint & RemoteEndpoint)
{
	SocketAddress Address = RemoteEndpoint.Serialize();
	Elysium::Core::int32_t AddressLength = Address.GetSize();
	
	Elysium::Core::int32_t BytesReceived = recvfrom(_WinSocketHandle, (char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count),
		static_cast<const Elysium::Core::int32_t>(SocketFlags), (sockaddr*)&Address, &AddressLength);
	if (BytesReceived == SOCKET_ERROR)
	{
		throw SocketException();
	}

	return BytesReceived;
}

const size_t Elysium::Core::Net::Sockets::Socket::Send(const Elysium::Core::byte * Buffer, const size_t Count)
{
	Elysium::Core::int32_t BytesSent = send(_WinSocketHandle, (const char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count), 0);
	if (BytesSent == SOCKET_ERROR)
	{
		throw SocketException();
	}

	return BytesSent;
}

const size_t Elysium::Core::Net::Sockets::Socket::SendTo(const Elysium::Core::byte * Buffer, const size_t Count, const EndPoint & RemoteEndpoint)
{
	return SendTo(Buffer, Count, SocketFlags::None, RemoteEndpoint);
}

const size_t Elysium::Core::Net::Sockets::Socket::SendTo(const Elysium::Core::byte * Buffer, const size_t Count, const SocketFlags SocketFlags, const EndPoint & RemoteEndpoint)
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

const Elysium::Core::Net::Sockets::AcceptAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginAccept(const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void * State)
{
	AcceptAsyncResult* AsyncResult = new AcceptAsyncResult(this, Callback, State, 8192);
	AsyncResult->_Overlapped.Pointer = AsyncResult;
	AsyncResult->_ClientSocket = WSASocket(FormatConverter::Convert(GetAddressFamily()), FormatConverter::Convert(GetSocketType()),
		FormatConverter::Convert(GetProtocolType()), nullptr, 0, WSA_FLAG_OVERLAPPED);
	
	//SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ConditionalAccept, true);

	StartThreadpoolIo(_CompletionPortHandle);
	Elysium::Core::int32_t Result = AcceptEx(_WinSocketHandle, AsyncResult->_ClientSocket, (void*)&AsyncResult->_Addresses[0], 0, 44, 44, nullptr, &AsyncResult->_Overlapped);
	if (Result == SOCKET_ERROR)
	{
		if (WSAGetLastError() != static_cast<Elysium::Core::int32_t>(SocketError::IOPending))
		{
			CancelThreadpoolIo(_CompletionPortHandle);
			delete AsyncResult;
			throw SocketException();
		}
	}

	return AsyncResult;
}
Elysium::Core::Net::Sockets::Socket Elysium::Core::Net::Sockets::Socket::EndAccept(const Elysium::Core::IAsyncResult * Result)
{
	AcceptAsyncResult* CastResult = (AcceptAsyncResult*)Result;

	return Elysium::Core::Net::Sockets::Socket(CastResult->_ClientSocket);
}

const Elysium::Core::IAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginConnect(const Elysium::Core::Net::EndPoint & RemoteEndPoint, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void * State)
{
	// ConnectEx requires the socket to be bound!
	Elysium::Core::Net::IPEndPoint LocalEndPoint = Elysium::Core::Net::IPEndPoint(Elysium::Core::Net::IPAddress::Any(), 0);
	Bind(LocalEndPoint);

	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(this, Callback, State, 8192);
	AsyncResult->_WSABuffer.len = 0;
	AsyncResult->_WSABuffer.buf = nullptr;
	AsyncResult->_Overlapped.Pointer = AsyncResult;

	StartThreadpoolIo(_CompletionPortHandle);
	const SocketAddress Address = RemoteEndPoint.Serialize();
	bool Result = ConnectEx(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize(), nullptr, 0, nullptr, &AsyncResult->_Overlapped);
	if (!Result)
	{
		if (WSAGetLastError() != static_cast<Elysium::Core::int32_t>(SocketError::IOPending))
		{
			throw SocketException();
		}
	}

	return AsyncResult;
}

void Elysium::Core::Net::Sockets::Socket::EndConnect(const Elysium::Core::IAsyncResult * Result, Elysium::Core::Net::Sockets::SocketError & ErrorCode)
{
	// ToDo: read error
}

const Elysium::Core::IAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginDisconnect(const bool ReuseSocket, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void * State)
{
	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(this, Callback, State, 8192);
	AsyncResult->_WSABuffer.len = 0;
	AsyncResult->_WSABuffer.buf = nullptr;
	AsyncResult->_Overlapped.Pointer = AsyncResult;

	StartThreadpoolIo(_CompletionPortHandle);
	bool Result = DisconnectEx(_WinSocketHandle, &AsyncResult->_Overlapped, 0, 0);
	if (!Result)
	{
		if (WSAGetLastError() != static_cast<Elysium::Core::int32_t>(SocketError::IOPending))
		{
			throw SocketException();
		}
	}

	return AsyncResult;
}

void Elysium::Core::Net::Sockets::Socket::EndDisconnect(const Elysium::Core::IAsyncResult * Result)
{
	// ToDo: read error?
}

const Elysium::Core::IAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginReceive(const Elysium::Core::byte * Buffer, const size_t Size, SocketFlags Flags, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void * State)
{
	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(this, Callback, State, 8192);
	AsyncResult->_WSABuffer.len = Size;
	AsyncResult->_WSABuffer.buf = (char*)Buffer;
	AsyncResult->_Overlapped.Pointer = AsyncResult;

	StartThreadpoolIo(_CompletionPortHandle);
	Elysium::Core::int32_t Result = WSARecv(_WinSocketHandle, (LPWSABUF)&AsyncResult->_WSABuffer, 1, (LPDWORD)&AsyncResult->_BytesTransferred, (LPDWORD)&Flags,
		&AsyncResult->_Overlapped, nullptr);
	if (Result == SOCKET_ERROR)
	{
		if (WSAGetLastError() != static_cast<Elysium::Core::int32_t>(SocketError::IOPending))
		{
			CancelThreadpoolIo(_CompletionPortHandle);
			delete AsyncResult;
			throw SocketException();
		}
	}
	
	return AsyncResult;
}

const size_t Elysium::Core::Net::Sockets::Socket::EndReceive(const Elysium::Core::IAsyncResult * Result, Elysium::Core::Net::Sockets::SocketError & ErrorCode)
{
	SendReceiveAsyncResult* CastResult = (SendReceiveAsyncResult*)Result;

	return CastResult->_BytesTransferred;
}

const Elysium::Core::IAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginSend(const Elysium::Core::byte * Buffer, const size_t Size, SocketFlags Flags, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void * State)
{
	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(this, Callback, State, 8192);
	AsyncResult->_WSABuffer.len = Size;
	AsyncResult->_WSABuffer.buf = (char*)Buffer;
	AsyncResult->_Overlapped.Pointer = AsyncResult;

	StartThreadpoolIo(_CompletionPortHandle);
	Elysium::Core::int32_t Result = WSASend(_WinSocketHandle, (LPWSABUF)&AsyncResult->_WSABuffer, 1, (LPDWORD)&AsyncResult->_BytesTransferred, (DWORD)Flags,
		&AsyncResult->_Overlapped, nullptr);
	if (Result == SOCKET_ERROR)
	{
		if (WSAGetLastError() != static_cast<Elysium::Core::int32_t>(SocketError::IOPending))
		{
			CancelThreadpoolIo(_CompletionPortHandle);
			delete AsyncResult;
			throw SocketException();
		}
	}

	return AsyncResult;
}

const size_t Elysium::Core::Net::Sockets::Socket::EndSend(const Elysium::Core::IAsyncResult * Result, Elysium::Core::Net::Sockets::SocketError & ErrorCode)
{
	SendReceiveAsyncResult* CastResult = (SendReceiveAsyncResult*)Result;

	return CastResult->_BytesTransferred;
}

Elysium::Core::Net::Sockets::Socket::Socket(SOCKET WinSocketHandle)
	: _WinSocketHandle(WinSocketHandle), _CompletionPortHandle(nullptr), ConnectEx(nullptr), DisconnectEx(nullptr)
{
	InitializeWinSockAPI();

	_CompletionPortHandle = CreateThreadpoolIo((HANDLE)_WinSocketHandle, (PTP_WIN32_IO_CALLBACK)&IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::_IOPool._Environment);
	RetrieveFunctions();
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

void Elysium::Core::Net::Sockets::Socket::RetrieveFunctions()
{
	DWORD BytesReturned = 0;
	GUID GuidConnectEx = WSAID_CONNECTEX;
	GUID GuidDisconnectEx = WSAID_DISCONNECTEX;

	Elysium::Core::int32_t ResultConnectEx = WSAIoctl(_WinSocketHandle, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidConnectEx, sizeof(GuidConnectEx), &ConnectEx,
		sizeof(ConnectEx), &BytesReturned, nullptr, nullptr);
	if (ResultConnectEx == SOCKET_ERROR)
	{
		throw SocketException();
	}

	Elysium::Core::int32_t ResultDisconnectEx = WSAIoctl(_WinSocketHandle, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidDisconnectEx, sizeof(GuidDisconnectEx), &DisconnectEx,
		sizeof(DisconnectEx), &BytesReturned, nullptr, nullptr);
	if (ResultDisconnectEx == SOCKET_ERROR)
	{
		throw SocketException();
	}
}


void Elysium::Core::Net::Sockets::Socket::IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void * Context, void * Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
{
	Elysium::Core::Net::Sockets::Socket* Socket = (Elysium::Core::Net::Sockets::Socket*)Context;
	//CancelThreadpoolIo(Socket->_CompletionPortHandle);

	Elysium::Core::IAsyncResult* AsyncResult = (Elysium::Core::IAsyncResult*)((LPOVERLAPPED)Overlapped)->Pointer;
	if (AsyncResult != nullptr)
	{
		SendReceiveAsyncResult* TriggeredSendReceiveAsyncResult = dynamic_cast<SendReceiveAsyncResult*>(AsyncResult);
		if (TriggeredSendReceiveAsyncResult != nullptr)
		{
			TriggeredSendReceiveAsyncResult->_BytesTransferred = NumberOfBytesTransferred;

			const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback = TriggeredSendReceiveAsyncResult->GetCallback();
			Callback(AsyncResult);
		}

		AcceptAsyncResult* TriggeredAcceptAsyncResult = dynamic_cast<AcceptAsyncResult*>(AsyncResult);
		if (TriggeredAcceptAsyncResult != nullptr)
		{
			const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback = TriggeredAcceptAsyncResult->GetCallback();
			Callback(AsyncResult);
		}
	}
}
