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
}
void Elysium::Core::IO::MemoryStream::SetPosition(int64_t Position)
{
	if (!GetCanSeek())
	{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		throw NotSupportedException();
#elif defined(__ANDROID__)
		// ToDo: cannot use 'throw' with exceptions disabled
		//throw NotSupportedException();
#else
#error "undefined os"
#endif
	}

	_CurrentPosition = (size_t)Position;
}

void Elysium::Core::IO::MemoryStream::SetCapacity(size_t Capacity)
{
	if (Capacity > UINT_MAX)
	{	// ToDo: throw a specific ArgumentOutOfRangeException
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		throw Exception(L"ArgumentOutOfRangeException");
#elif defined(__ANDROID__)
		// ToDo: cannot use 'throw' with exceptions disabled
		//throw Exception("ArgumentOutOfRangeException");
#else
#error "undefined os"
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
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		throw NotSupportedException();
#elif defined(__ANDROID__)
		// ToDo: cannot use 'throw' with exceptions disabled
		//throw NotSupportedException();
#else
#error "undefined os"
#endif
	}
}
int Elysium::Core::IO::MemoryStream::Read(BYTE * Buffer, const int Offset, const int Count)
{
	if (!GetCanRead())
	{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		throw NotSupportedException();
#elif defined(__ANDROID__)
		// ToDo: cannot use 'throw' with exceptions disabled
		//throw NotSupportedException();
#else
#error "undefined os"
#endif
	}

	int BytesToRead = _Buffer.GetCount() - _CurrentPosition;
	if (BytesToRead > Count)
	{
		BytesToRead = Count;
	}
	if (BytesToRead <= 0)
	{
		return 0;
	}

	if (BytesToRead <= 8)
	{	// ToDo: is this actually faster with up to eight bytes?
		int ByteCount = BytesToRead;
		while (--ByteCount >= 0)
		{
			Buffer[Offset + ByteCount] = _Buffer[_CurrentPosition + ByteCount];
		}
	}
	else
	{
		memcpy(&Buffer[0], &_Buffer[Offset + _CurrentPosition], BytesToRead);
	}
	_CurrentPosition += BytesToRead;

	return BytesToRead;
}
void Elysium::Core::IO::MemoryStream::Write(const BYTE * Buffer, const int Offset, const int Count)
{
	if (!GetCanWrite())
	{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		throw NotSupportedException();
#elif defined(__ANDROID__)
		// ToDo: cannot use 'throw' with exceptions disabled
		//throw NotSupportedException();
#else
#error "undefined os"
#endif
	}

	_Buffer.AddRange(Buffer, Offset, Count);
}
