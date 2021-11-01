#include "MemoryStream.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "../Elysium.Core/ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#include <iostream>

Elysium::Core::IO::MemoryStream::MemoryStream()
	: Elysium::Core::IO::Stream()
{ }
Elysium::Core::IO::MemoryStream::MemoryStream(const Elysium::Core::size Capacity)
	: Elysium::Core::IO::Stream(),
	_Buffer(Collections::Template::List<byte>(Capacity))
{ }
Elysium::Core::IO::MemoryStream::MemoryStream(const byte* Data, Elysium::Core::size Length)
	: Elysium::Core::IO::Stream(),
	_Buffer(Collections::Template::List<byte>(Length))
{
	std::memcpy(&_Buffer[0], &Data[0], Length);
}
Elysium::Core::IO::MemoryStream::MemoryStream(const Collections::Template::Array<byte>& Data, Elysium::Core::size Offset, Elysium::Core::size Length)
	: Elysium::Core::IO::Stream(),
	_Buffer(Collections::Template::List<byte>(Length))
{ 
	std::memcpy(&_Buffer[0], &Data[Offset], Length);
}
Elysium::Core::IO::MemoryStream::~MemoryStream()
{ }

const bool Elysium::Core::IO::MemoryStream::GetCanRead() const
{
	return true;
}

const bool Elysium::Core::IO::MemoryStream::GetCanSeek() const
{
	return true;
}

const bool Elysium::Core::IO::MemoryStream::GetCanTimeout() const
{
	return Elysium::Core::IO::Stream::GetCanTimeout();
}

const bool Elysium::Core::IO::MemoryStream::GetCanWrite() const
{
	return true;
}

const Elysium::Core::size Elysium::Core::IO::MemoryStream::GetLength() const
{
	return _Buffer.GetCount();
}

const Elysium::Core::uint64_t Elysium::Core::IO::MemoryStream::GetPosition() const
{
	return _CurrentPosition;
}

const Elysium::Core::uint32_t Elysium::Core::IO::MemoryStream::GetReadTimeout() const
{
	return Elysium::Core::IO::Stream::GetReadTimeout();
}

const Elysium::Core::uint32_t Elysium::Core::IO::MemoryStream::GetWriteTimeout() const
{
	return Elysium::Core::IO::Stream::GetWriteTimeout();
}

const Elysium::Core::size Elysium::Core::IO::MemoryStream::GetCapacity() const
{
	return _Buffer.GetCapacity();
}

void Elysium::Core::IO::MemoryStream::SetLength(const Elysium::Core::size Value)
{
	/*
	if (Value > _Buffer.capacity())
	{
		throw NotSupportedException();
	}
	*/
	throw NotImplementedException();
}
void Elysium::Core::IO::MemoryStream::SetPosition(const Elysium::Core::uint64_t Position)
{
	if (!GetCanSeek())
	{
		throw NotSupportedException();
	}

	_CurrentPosition = (Elysium::Core::size)Position;
}

void Elysium::Core::IO::MemoryStream::SetCapacity(const Elysium::Core::size Capacity)
{
	if (Capacity > UINT_MAX)
	{
		throw ArgumentOutOfRangeException();
	}

	_Buffer.SetCapacity(Capacity);
}

void Elysium::Core::IO::MemoryStream::Close()
{ }

void Elysium::Core::IO::MemoryStream::Flush()
{ }

const Elysium::Core::size Elysium::Core::IO::MemoryStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{
	if (!GetCanSeek())
	{
		throw NotSupportedException();
	}

	throw NotImplementedException();
}

const Elysium::Core::size Elysium::Core::IO::MemoryStream::Read(Elysium::Core::byte * Buffer, const Elysium::Core::size Count)
{
	if (!GetCanRead())
	{
		throw NotSupportedException();
	}

	Elysium::Core::size BytesToRead = _Buffer.GetCount() - _CurrentPosition;
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
	{	// ToDo: is this actually faster with up to eight bytes? also this code obviously will need to be refactored because of ByteCount being Elysium::Core::size
		Elysium::Core::size ByteCount = BytesToRead;
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

Elysium::Core::byte Elysium::Core::IO::MemoryStream::ReadByte()
{
	if (_CurrentPosition >= _Buffer.GetCount())
	{
		return -1;
	}

	return static_cast<int32_t>(_Buffer[_CurrentPosition++]);
}

void Elysium::Core::IO::MemoryStream::Write(const Elysium::Core::byte * Buffer, const Elysium::Core::size Count)
{
	if (!GetCanWrite())
	{
		throw NotSupportedException();
	}

	_Buffer.AddRange(Buffer, Count);
}
