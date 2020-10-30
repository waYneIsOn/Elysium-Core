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

bool Elysium::Core::Net::Sockets::NetworkStream::GetCanRead() const
{
	throw NotImplementedException();
}
bool Elysium::Core::Net::Sockets::NetworkStream::GetCanSeek() const
{
	throw NotImplementedException();
}
bool Elysium::Core::Net::Sockets::NetworkStream::GetCanTimeout() const
{
	throw NotImplementedException();
}
bool Elysium::Core::Net::Sockets::NetworkStream::GetCanWrite() const
{
	throw NotImplementedException();
}

const size_t Elysium::Core::Net::Sockets::NetworkStream::GetLength()
{
	throw NotImplementedException();
}
const __int64 Elysium::Core::Net::Sockets::NetworkStream::GetPosition()
{
	throw NotImplementedException();
}
const int Elysium::Core::Net::Sockets::NetworkStream::GetReadTimeout() const
{
	throw NotImplementedException();
}
const int Elysium::Core::Net::Sockets::NetworkStream::GetWriteTimeout() const
{
	throw NotImplementedException();
}

const Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::NetworkStream::GetSocket() const
{
	return _Socket;
}

void Elysium::Core::Net::Sockets::NetworkStream::SetLength(size_t Value)
{
	throw NotImplementedException();
}
void Elysium::Core::Net::Sockets::NetworkStream::SetPosition(__int64 Position)
{
	throw NotImplementedException();
}
void Elysium::Core::Net::Sockets::NetworkStream::SetReadTimeout(int Value)
{
	throw NotImplementedException();
}
void Elysium::Core::Net::Sockets::NetworkStream::SetWriteTimeout(int Value)
{
	throw NotImplementedException();
}

void Elysium::Core::Net::Sockets::NetworkStream::Close()
{
	if (_OwnsSocket)
	{
		_Socket.Disconnect(true);
	}
}
void Elysium::Core::Net::Sockets::NetworkStream::Flush()
{
	// do nothing
}
void Elysium::Core::Net::Sockets::NetworkStream::Seek(const __int64 Offset, const Elysium::Core::IO::SeekOrigin Origin)
{
	throw NotImplementedException();
}
size_t Elysium::Core::Net::Sockets::NetworkStream::Read(byte * Buffer, const size_t Count)
{
	return _Socket.Receive(&Buffer[0], Count);
}
Elysium::Core::byte Elysium::Core::Net::Sockets::NetworkStream::ReadByte()
{
	byte Buffer;
	size_t BytesRead = _Socket.Receive(&Buffer, 1);

	return static_cast<int32_t>(Buffer);
}
void Elysium::Core::Net::Sockets::NetworkStream::Write(const byte * Buffer, const size_t Count)
{
	size_t BytesSent = _Socket.Send(&Buffer[0], Count);
}
