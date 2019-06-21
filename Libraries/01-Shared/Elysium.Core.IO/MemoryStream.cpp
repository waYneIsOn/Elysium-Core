#include "MemoryStream.hpp"

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::IO::MemoryStream::MemoryStream()
	: Elysium::Core::IO::Stream()
{
}
Elysium::Core::IO::MemoryStream::~MemoryStream()
{
}

bool Elysium::Core::IO::MemoryStream::GetCanRead() const
{
	return true;
}
bool Elysium::Core::IO::MemoryStream::GetCanSeek() const
{
	return true;
}
bool Elysium::Core::IO::MemoryStream::GetCanTimeout() const
{
	return Elysium::Core::IO::Stream::GetCanTimeout();
}
bool Elysium::Core::IO::MemoryStream::GetCanWrite() const
{
	return true;
}

size_t Elysium::Core::IO::MemoryStream::GetLength() const
{
	return _Buffer.GetCount();
}
int64_t Elysium::Core::IO::MemoryStream::GetPosition() const
{
	return Elysium::Core::IO::Stream::GetPosition();
}
int Elysium::Core::IO::MemoryStream::GetReadTimeout() const
{
	return Elysium::Core::IO::Stream::GetReadTimeout();
}
int Elysium::Core::IO::MemoryStream::GetWriteTimeout() const
{
	return Elysium::Core::IO::Stream::GetWriteTimeout();
}

size_t Elysium::Core::IO::MemoryStream::GetCapacity() const
{
	return _Buffer.GetCapacity();
}

void Elysium::Core::IO::MemoryStream::SetLength(size_t Value)
{
	/*
	if (Value > _Buffer.capacity())
	{
		throw NotSupportedException();
	}
	*/
	throw NotImplementedException();
}
void Elysium::Core::IO::MemoryStream::SetPosition(int64_t Position)
{
	if (!GetCanSeek())
	{
		throw NotSupportedException();
	}

	_CurrentPosition = (size_t)Position;
}

void Elysium::Core::IO::MemoryStream::SetCapacity(size_t Capacity)
{
	if (Capacity > UINT_MAX)
	{	// ToDo: throw a specific ArgumentOutOfRangeException
#ifdef UNICODE
		throw Exception(L"ArgumentOutOfRangeException");
#else
		throw Exception("ArgumentOutOfRangeException");
#endif
	}

	_Buffer.SetCapacity(Capacity);
}

void Elysium::Core::IO::MemoryStream::Close()
{
}
void Elysium::Core::IO::MemoryStream::Flush()
{
}
void Elysium::Core::IO::MemoryStream::Seek(const int64_t Offset, const SeekOrigin Origin)
{
	if (!GetCanSeek())
	{
		throw NotSupportedException();
	}
}
size_t Elysium::Core::IO::MemoryStream::Read(byte * Buffer, const size_t Count)
{
	if (!GetCanRead())
	{
		throw NotSupportedException();
	}

	size_t BytesToRead = _Buffer.GetCount() - _CurrentPosition;
	if (BytesToRead > Count)
	{
		BytesToRead = Count;
	}
	if (BytesToRead <= 0)
	{
		return 0;
	}
	/*
	if (BytesToRead <= 8)
	{	// ToDo: is this actually faster with up to eight bytes? also this code obviously will need to be refactored because of ByteCount being size_t
		size_t ByteCount = BytesToRead;
		while (--ByteCount >= 0)
		{
			Buffer[Offset + ByteCount] = _Buffer[_CurrentPosition + ByteCount];
		}
	}
	else
	{
		memcpy(&Buffer[0], &_Buffer[Offset + _CurrentPosition], BytesToRead);
	}
	*/
	memcpy(&Buffer[0], &_Buffer[_CurrentPosition], BytesToRead);
	_CurrentPosition += BytesToRead;

	return BytesToRead;
}
void Elysium::Core::IO::MemoryStream::Write(const byte * Buffer, const size_t Count)
{
	if (!GetCanWrite())
	{
		throw NotSupportedException();
	}

	_Buffer.AddRange(Buffer, Count);
}
