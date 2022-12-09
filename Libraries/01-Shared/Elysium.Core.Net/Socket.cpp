#include "Socket.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_BITCONVERTER
#include "../Elysium.Core/BitConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_DNSENDPOINT
#include "DnsEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_FORMATCONVERTER
#include "FormatConverter.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_IPENDPOINT
#include "IPEndPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKETEXCEPTION
#include "SocketException.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../Elysium.Core.Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
Elysium::Core::Net::Sockets::Socket::Socket(SOCKET WinSocketHandle)
	: _WinSocketHandle(WinSocketHandle), 
	_CompletionPortHandle(CreateThreadpoolIo((HANDLE)_WinSocketHandle, (PTP_WIN32_IO_CALLBACK)&IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::_IOPool._Environment)),
	ConnectEx(Internal::WinSocket::RetrieveFunctionConnectEx(_WinSocketHandle)),
	DisconnectEx(Internal::WinSocket::RetrieveFunctionDisconnectEx(_WinSocketHandle))
{ }
#endif

Elysium::Core::Net::Sockets::Socket::Socket(AddressFamily AddressFamily, SocketType SocketType, ProtocolType ProtocolType)
	: _WinSocketHandle(WSASocket(FormatConverter::Convert(AddressFamily), FormatConverter::Convert(SocketType), FormatConverter::Convert(ProtocolType), nullptr, 0, WSA_FLAG_OVERLAPPED)),
	_CompletionPortHandle(CreateThreadpoolIo((HANDLE)_WinSocketHandle, (PTP_WIN32_IO_CALLBACK)&IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::_IOPool._Environment)),
	ConnectEx(Internal::WinSocket::RetrieveFunctionConnectEx(_WinSocketHandle)),
	DisconnectEx(Internal::WinSocket::RetrieveFunctionDisconnectEx(_WinSocketHandle))
{
	if (_CompletionPortHandle == nullptr)
	{
		throw SocketException();
	}
	if (_WinSocketHandle == INVALID_SOCKET)
	{
		throw SocketException();
	}
}

Elysium::Core::Net::Sockets::Socket::Socket(Socket && Right) noexcept
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Net::Sockets::Socket::~Socket()
{
	if (_CompletionPortHandle != nullptr)
	{
		/*
		* It is necessary to wait for any pending io callbacks here or I'm going to cause a memory leak!
		*
		* Imagine a scenario where in a scope a Socket gets created on the stack and BeginRead(...) gets called.
		* As soon as the scope ends, the Socket gets deleted and it's io completion port canceled (due to this very destructor).
		* This means Socket::IOCompletionPortCallback(...), where the IAsyncResult - created on the heap by BeginRead(...) -
		* would be deleted, is NOT going to be called.
		* Therefore it is also imperative I do not cancel any pending notifications.
		* 
		* ToDo: 
		* While this MIGHT be fine for a FileStream, this behaviour might not be feasible for a Socket.
		* Imagine a server with a single connected client waiting for it to send something and it doesn't!
		*/
		//CancelThreadpoolIo(_CompletionPortHandle);
		WaitForThreadpoolIoCallbacks(_CompletionPortHandle, FALSE);
		CloseThreadpoolIo(_CompletionPortHandle);

		_CompletionPortHandle = nullptr;
	}

	if (_WinSocketHandle != INVALID_SOCKET)
	{
		// ToDo: this needs to be handled correctly (only close after we've received the "current message", blocking/non-blocking etc.)
		Close();
	}
}

Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::Socket::operator=(Socket && Right) noexcept
{
	if (this != &Right)
	{
		_WinSocketHandle = Elysium::Core::Template::Functional::Move(Right._WinSocketHandle);
		_CompletionPortHandle = Elysium::Core::Template::Functional::Move(Right._CompletionPortHandle);
		ConnectEx = Elysium::Core::Template::Functional::Move(Right.ConnectEx);
		DisconnectEx = Elysium::Core::Template::Functional::Move(Right.DisconnectEx);

		Right._WinSocketHandle = INVALID_SOCKET;
		Right._CompletionPortHandle = 0;
		Right.ConnectEx = nullptr;
		Right.DisconnectEx = nullptr;
	}
	return *this;
}

const Elysium::Core::Net::Sockets::AddressFamily Elysium::Core::Net::Sockets::Socket::GetAddressFamily() const
{
	WSAPROTOCOL_INFO proto;
	WSADuplicateSocket(_WinSocketHandle, GetCurrentProcessId(), &proto);
	return static_cast<Elysium::Core::Net::Sockets::AddressFamily>(proto.iAddressFamily);
}

const Elysium::Core::Net::Sockets::SocketType Elysium::Core::Net::Sockets::Socket::GetSocketType() const
{
	WSAPROTOCOL_INFO proto;
	WSADuplicateSocket(_WinSocketHandle, GetCurrentProcessId(), &proto);
	return static_cast<Elysium::Core::Net::Sockets::SocketType>(proto.iSocketType);
}

const Elysium::Core::Net::Sockets::ProtocolType Elysium::Core::Net::Sockets::Socket::GetProtocolType() const
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

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::IOControl(const IOControlCode ControlCode, const Elysium::Core::uint32_t OptionInValue, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength)
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Bytes = BitConverter::GetBytes(OptionInValue);
	return IOControl(static_cast<const Elysium::Core::int32_t>(ControlCode), &Bytes[0], Bytes.GetLength(), OptionOutValue, OptionOutValueLength);
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::IOControl(const IOControlCode ControlCode, const Elysium::Core::byte * OptionInValue, const Elysium::Core::size OptionInValueLength, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength)
{
	return IOControl(static_cast<const Elysium::Core::int32_t>(ControlCode), OptionInValue, OptionInValueLength, OptionOutValue, OptionOutValueLength);
}

const Elysium::Core::int32_t Elysium::Core::Net::Sockets::Socket::IOControl(const Elysium::Core::int32_t ControlCode, const Elysium::Core::byte * OptionInValue, const Elysium::Core::size OptionInValueLength, Elysium::Core::byte * OptionOutValue, const Elysium::Core::size OptionOutValueLength)
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

void Elysium::Core::Net::Sockets::Socket::Select(Elysium::Core::Template::Container::Vector<Socket*>* CheckRead, Elysium::Core::Template::Container::Vector<Socket*>* CheckWrite, Elysium::Core::Template::Container::Vector<Socket*>* CheckError, const Elysium::Core::int32_t MicroSeconds)
{
	fd_set ReadSet = fd_set();
	fd_set WriteSet = fd_set();
	fd_set ErrorSet = fd_set();

	FD_ZERO(&ReadSet);
	FD_ZERO(&WriteSet);
	FD_ZERO(&ErrorSet);

	if (CheckRead != nullptr)
	{
		for (Elysium::Core::size i = 0; i < CheckRead->GetLength(); i++)
		{
			FD_SET(CheckRead->operator[](i)->_WinSocketHandle, &ReadSet);
		}
	}
	if (CheckWrite != nullptr)
	{
		for (Elysium::Core::size i = 0; i < CheckWrite->GetLength(); i++)
		{
			FD_SET(CheckWrite->operator[](i)->_WinSocketHandle, &WriteSet);
		}
	}
	if (CheckError != nullptr)
	{
		for (Elysium::Core::size i = 0; i < CheckError->GetLength(); i++)
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
		for (Elysium::Core::size i = CheckRead->GetLength(); i > 0; i--)
		{
			if (!FD_ISSET(CheckRead->operator[](i - 1)->_WinSocketHandle, &ReadSet))
			{
				CheckRead->EraseAt(i - 1);
			}
		}
	}
	if (CheckWrite != nullptr)
	{
		for (Elysium::Core::size i = CheckWrite->GetLength(); i > 0; i--)
		{
			if (!FD_ISSET(CheckWrite->operator[](i - 1)->_WinSocketHandle, &WriteSet))
			{
				CheckWrite->EraseAt(i - 1);
			}
		}
	}
	if (CheckError != nullptr)
	{
		for (Elysium::Core::size i = CheckError->GetLength(); i > 0; i--)
		{
			if (!FD_ISSET(CheckError->operator[](i - 1)->_WinSocketHandle, &ErrorSet))
			{
				CheckError->EraseAt(i - 1);
			}
		}
	}
}

void Elysium::Core::Net::Sockets::Socket::Select(Elysium::Core::Template::Container::Vector<Socket*>* CheckRead, Elysium::Core::Template::Container::Vector<Socket*>* CheckWrite, Elysium::Core::Template::Container::Vector<Socket*>* CheckError, const Elysium::Core::TimeSpan Duration)
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

void Elysium::Core::Net::Sockets::Socket::Connect(const Utf8String& Host, const Elysium::Core::uint16_t Port)
{
	// ToDo: parse host to decide whether to use IpEndPoint or DnsEndPoint (can be done easily once I got regex working)
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

	Shutdown(SocketShutdown::Both);
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

const Elysium::Core::size Elysium::Core::Net::Sockets::Socket::Receive(const Elysium::Core::byte * Buffer, const Elysium::Core::size Count)
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

const Elysium::Core::size Elysium::Core::Net::Sockets::Socket::ReceiveFrom(const Elysium::Core::byte * Buffer, const Elysium::Core::size Count, EndPoint & RemoteEndpoint)
{
	return ReceiveFrom(Buffer, Count, SocketFlags::None, RemoteEndpoint);
}

const Elysium::Core::size Elysium::Core::Net::Sockets::Socket::ReceiveFrom(const Elysium::Core::byte * Buffer, const Elysium::Core::size Count, const SocketFlags SocketFlags, EndPoint & RemoteEndpoint)
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

const Elysium::Core::size Elysium::Core::Net::Sockets::Socket::Send(const Elysium::Core::byte * Buffer, const Elysium::Core::size Count)
{
	Elysium::Core::int32_t BytesSent = send(_WinSocketHandle, (const char*)&Buffer[0], static_cast<const Elysium::Core::int32_t>(Count), 0);
	if (BytesSent == SOCKET_ERROR)
	{
		throw SocketException();
	}

	return BytesSent;
}

const Elysium::Core::size Elysium::Core::Net::Sockets::Socket::SendTo(const Elysium::Core::byte * Buffer, const Elysium::Core::size Count, const EndPoint & RemoteEndpoint)
{
	return SendTo(Buffer, Count, SocketFlags::None, RemoteEndpoint);
}

const Elysium::Core::size Elysium::Core::Net::Sockets::Socket::SendTo(const Elysium::Core::byte * Buffer, const Elysium::Core::size Count, const SocketFlags SocketFlags, const EndPoint & RemoteEndpoint)
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

Elysium::Core::IAsyncResult* Elysium::Core::Net::Sockets::Socket::BeginAccept(const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State)
{
	AcceptAsyncResult* AsyncResult = new AcceptAsyncResult(*this, Callback, State, 8192);
	AsyncResult->_ClientSocket = WSASocket(FormatConverter::Convert(GetAddressFamily()), FormatConverter::Convert(GetSocketType()),
		FormatConverter::Convert(GetProtocolType()), nullptr, 0, WSA_FLAG_OVERLAPPED);

	StartThreadpoolIo(_CompletionPortHandle);
	Elysium::Core::int32_t Result = AcceptEx(_WinSocketHandle, AsyncResult->_ClientSocket, (void*)&AsyncResult->_Addresses[0], 0, 44, 44, nullptr, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap);
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

const Elysium::Core::Net::Sockets::Socket Elysium::Core::Net::Sockets::Socket::EndAccept(const Elysium::Core::IAsyncResult* Result)
{
	Elysium::Core::Net::Sockets::AcceptAsyncResult* AsyncAcceptResult = (Elysium::Core::Net::Sockets::AcceptAsyncResult*)Result;
	return Elysium::Core::Net::Sockets::Socket(AsyncAcceptResult->_ClientSocket);
}

Elysium::Core::IAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginConnect(const Elysium::Core::Net::EndPoint & RemoteEndPoint, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void * State)
{
	// ConnectEx requires the socket to be bound!
	Elysium::Core::Net::IPEndPoint LocalEndPoint = Elysium::Core::Net::IPEndPoint(Elysium::Core::Net::IPAddress::Any(), 0);
	Bind(LocalEndPoint);

	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(*this, Callback, State);
	AsyncResult->_WSABuffer.len = 0;
	AsyncResult->_WSABuffer.buf = nullptr;

	StartThreadpoolIo(_CompletionPortHandle);
	const SocketAddress Address = RemoteEndPoint.Serialize();
	bool Result = ConnectEx(_WinSocketHandle, (const sockaddr*)&Address, Address.GetSize(), nullptr, 0, nullptr, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap);
	if (!Result)
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

void Elysium::Core::Net::Sockets::Socket::EndConnect(const Elysium::Core::IAsyncResult * Result, Elysium::Core::Net::Sockets::SocketError & ErrorCode)
{
	// ToDo: read error
}

Elysium::Core::IAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginDisconnect(const bool ReuseSocket, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void * State)
{
	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(*this, Callback, State);
	AsyncResult->_WSABuffer.len = 0;
	AsyncResult->_WSABuffer.buf = nullptr;

	StartThreadpoolIo(_CompletionPortHandle);
	bool Result = DisconnectEx(_WinSocketHandle, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap, 0, 0);
	if (!Result)
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

void Elysium::Core::Net::Sockets::Socket::EndDisconnect(const Elysium::Core::IAsyncResult * Result)
{
	// ToDo: read error?
}

Elysium::Core::IAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginReceive(const Elysium::Core::byte * Buffer, const Elysium::Core::size Size, SocketFlags Flags, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void * State)
{
	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(*this, Callback, State);
	AsyncResult->_WSABuffer.len = Size;
	AsyncResult->_WSABuffer.buf = (char*)Buffer;

	StartThreadpoolIo(_CompletionPortHandle);
	Elysium::Core::int32_t Result = WSARecv(_WinSocketHandle, (LPWSABUF)&AsyncResult->_WSABuffer, 1, (LPDWORD)&AsyncResult->_BytesTransferred, 
		(LPDWORD)&Flags, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap, nullptr);
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

const Elysium::Core::size Elysium::Core::Net::Sockets::Socket::EndReceive(const Elysium::Core::IAsyncResult * Result, Elysium::Core::Net::Sockets::SocketError & ErrorCode)
{
	SendReceiveAsyncResult* CastResult = (SendReceiveAsyncResult*)Result;

	return CastResult->_BytesTransferred;
}

Elysium::Core::IAsyncResult * Elysium::Core::Net::Sockets::Socket::BeginSend(const Elysium::Core::byte * Buffer, const Elysium::Core::size Size, SocketFlags Flags, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void * State)
{
	SendReceiveAsyncResult* AsyncResult = new SendReceiveAsyncResult(*this, Callback, State);
	AsyncResult->_WSABuffer.len = Size;
	AsyncResult->_WSABuffer.buf = (char*)Buffer;
	
	StartThreadpoolIo(_CompletionPortHandle);
	Elysium::Core::int32_t Result = WSASend(_WinSocketHandle, (LPWSABUF)&AsyncResult->_WSABuffer, 1, (LPDWORD)&AsyncResult->_BytesTransferred, 
		(DWORD)Flags, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap, nullptr);
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

const Elysium::Core::size Elysium::Core::Net::Sockets::Socket::EndSend(const Elysium::Core::IAsyncResult * Result, Elysium::Core::Net::Sockets::SocketError & ErrorCode)
{
	SendReceiveAsyncResult* CastResult = (SendReceiveAsyncResult*)Result;

	return CastResult->_BytesTransferred;
}

void Elysium::Core::Net::Sockets::Socket::IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void * Context, void * Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
{
	Elysium::Core::Internal::WrappedOverlap* WrappedOverlap = (Elysium::Core::Internal::WrappedOverlap*)Overlapped;
	Elysium::Core::IAsyncResult* AsyncResult = WrappedOverlap->_AsyncResult;
	
	AcceptAsyncResult* TriggeredAcceptAsyncResult = dynamic_cast<AcceptAsyncResult*>(AsyncResult);
	if (TriggeredAcceptAsyncResult != nullptr)
	{
		TriggeredAcceptAsyncResult->_ErrorCode = IoResult;

		((Elysium::Core::Threading::ManualResetEvent&)TriggeredAcceptAsyncResult->GetAsyncWaitHandle()).Set();

		TriggeredAcceptAsyncResult->GetCallback()(TriggeredAcceptAsyncResult);
	}

	SendReceiveAsyncResult* TriggeredSendReceiveAsyncResult = dynamic_cast<SendReceiveAsyncResult*>(AsyncResult);
	if (TriggeredSendReceiveAsyncResult != nullptr)
	{
		TriggeredSendReceiveAsyncResult->_ErrorCode = IoResult;
		TriggeredSendReceiveAsyncResult->_BytesTransferred = NumberOfBytesTransferred;

		((Elysium::Core::Threading::ManualResetEvent&)TriggeredSendReceiveAsyncResult->GetAsyncWaitHandle()).Set();

		TriggeredSendReceiveAsyncResult->GetCallback()(TriggeredSendReceiveAsyncResult);
	}

	delete AsyncResult;
}
