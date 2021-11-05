#include "NetworkStream.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Net::Sockets::NetworkStream::NetworkStream(Socket & Socket)
	: Elysium::Core::Net::Sockets::NetworkStream(Socket, false)
{ }
Elysium::Core::Net::Sockets::NetworkStream::NetworkStream(Socket & Socket, bool OwnsSocket)
	: Elysium::Core::IO::Stream(),
	_Socket(Socket),
	_OwnsSocket(OwnsSocket)
{ 
	if (_Socket.GetSocketType() != Elysium::Core::Net::Sockets::SocketType::Stream)
	{	// ToDo: throw according exception
		throw 1;
	}
}
Elysium::Core::Net::Sockets::NetworkStream::~NetworkStream()
{
	Close();
}

const bool Elysium::Core::Net::Sockets::NetworkStream::GetCanRead() const
{
	throw NotImplementedException();
}

const bool Elysium::Core::Net::Sockets::NetworkStream::GetCanSeek() const
{
	throw NotImplementedException();
}

const bool Elysium::Core::Net::Sockets::NetworkStream::GetCanTimeout() const
{
	throw NotImplementedException();
}

const bool Elysium::Core::Net::Sockets::NetworkStream::GetCanWrite() const
{
	throw NotImplementedException();
}

const Elysium::Core::size Elysium::Core::Net::Sockets::NetworkStream::GetLength() const
{
	throw NotImplementedException();
}

const Elysium::Core::uint64_t Elysium::Core::Net::Sockets::NetworkStream::GetPosition() const
{
	throw NotImplementedException();
}

const Elysium::Core::uint32_t Elysium::Core::Net::Sockets::NetworkStream::GetReadTimeout() const
{
	throw NotImplementedException();
}

const Elysium::Core::uint32_t Elysium::Core::Net::Sockets::NetworkStream::GetWriteTimeout() const
{
	throw NotImplementedException();
}

const Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::NetworkStream::GetSocket() const
{
	return _Socket;
}

void Elysium::Core::Net::Sockets::NetworkStream::SetLength(const Elysium::Core::size Value)
{
	throw NotImplementedException();
}

void Elysium::Core::Net::Sockets::NetworkStream::SetPosition(const Elysium::Core::uint64_t  Position)
{
	throw NotImplementedException();
}

void Elysium::Core::Net::Sockets::NetworkStream::SetReadTimeout(const Elysium::Core::uint32_t Value)
{
	throw NotImplementedException();
}

void Elysium::Core::Net::Sockets::NetworkStream::SetWriteTimeout(const Elysium::Core::uint32_t Value)
{
	throw NotImplementedException();
}

void Elysium::Core::Net::Sockets::NetworkStream::Close()
{
	if (_OwnsSocket)
	{
		_Socket.Close();
	}
}

void Elysium::Core::Net::Sockets::NetworkStream::Flush()
{ }

const Elysium::Core::size Elysium::Core::Net::Sockets::NetworkStream::Seek(const __int64 Offset, const Elysium::Core::IO::SeekOrigin Origin)
{
	throw NotImplementedException();
}

const Elysium::Core::size Elysium::Core::Net::Sockets::NetworkStream::Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
{
	return _Socket.Receive(&Buffer[0], Count);
}

Elysium::Core::byte Elysium::Core::Net::Sockets::NetworkStream::ReadByte()
{
	byte Buffer;
	Elysium::Core::size BytesRead = _Socket.Receive(&Buffer, 1);

	return static_cast<int32_t>(Buffer);
}

void Elysium::Core::Net::Sockets::NetworkStream::Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
{
	Elysium::Core::size TotalBytesSent = 0;
	while (TotalBytesSent < Count)
	{
		TotalBytesSent += _Socket.Send(&Buffer[TotalBytesSent], Count - TotalBytesSent);
	}
}
