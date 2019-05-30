#include "NetworkStream.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::Net::Sockets::NetworkStream::NetworkStream(Socket * Socket)
	: Elysium::Core::Net::Sockets::NetworkStream(Socket, false)
{
}
Elysium::Core::Net::Sockets::NetworkStream::NetworkStream(Socket * Socket, bool OwnsSocket)
	: Elysium::Core::IO::Stream(),
	_Socket(Socket),
	_OwnsSocket(OwnsSocket)
{
}
Elysium::Core::Net::Sockets::NetworkStream::~NetworkStream()
{
	if (_OwnsSocket)
	{
		_Socket->Disconnect(true);
		_Socket = nullptr;	// don't delete the object!
	}
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

size_t Elysium::Core::Net::Sockets::NetworkStream::GetLength() const
{
	throw NotImplementedException();
}
__int64 Elysium::Core::Net::Sockets::NetworkStream::GetPosition() const
{
	throw NotImplementedException();
}
int Elysium::Core::Net::Sockets::NetworkStream::GetReadTimeout() const
{
	throw NotImplementedException();
}
int Elysium::Core::Net::Sockets::NetworkStream::GetWriteTimeout() const
{
	throw NotImplementedException();
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
	throw NotImplementedException();
}
void Elysium::Core::Net::Sockets::NetworkStream::Flush()
{
	// do nothing
}
void Elysium::Core::Net::Sockets::NetworkStream::Seek(const __int64 Offset, const Elysium::Core::IO::SeekOrigin Origin)
{
	throw NotImplementedException();
}
int Elysium::Core::Net::Sockets::NetworkStream::Read(byte * Buffer, const int Offset, const int Count)
{
	return _Socket->Receive(&Buffer[0], Offset, Count);
}
void Elysium::Core::Net::Sockets::NetworkStream::Write(const byte * Buffer, const int Offset, const int Count)
{
	int BytesSent = _Socket->Send(&Buffer[0], Offset, Count);
}
