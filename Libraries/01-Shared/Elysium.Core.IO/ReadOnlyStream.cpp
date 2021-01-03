#include "ReadOnlyStream.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

Elysium::Core::IO::ReadOnlyStream::ReadOnlyStream(Stream& BaseStream, const Elysium::Core::uint64_t Start, const Elysium::Core::uint64_t End)
	: _BaseStream(BaseStream), _Start(Start), _End(End), _Position(Start)
{ }
Elysium::Core::IO::ReadOnlyStream::~ReadOnlyStream()
{ }

const bool Elysium::Core::IO::ReadOnlyStream::GetCanRead() const
{
	return _BaseStream.GetCanRead();
}

const bool Elysium::Core::IO::ReadOnlyStream::GetCanSeek() const
{
	return false;
}

const bool Elysium::Core::IO::ReadOnlyStream::GetCanTimeout() const
{
	return _BaseStream.GetCanTimeout();
}

const bool Elysium::Core::IO::ReadOnlyStream::GetCanWrite() const
{
	return false;
}

const size_t Elysium::Core::IO::ReadOnlyStream::GetLength() const
{
	return _End - _Start;
}

const Elysium::Core::uint64_t Elysium::Core::IO::ReadOnlyStream::GetPosition() const
{
	return _BaseStream.GetPosition() - _Start;
}

const Elysium::Core::uint32_t Elysium::Core::IO::ReadOnlyStream::GetReadTimeout() const
{
	return _BaseStream.GetReadTimeout();
}

const Elysium::Core::uint32_t Elysium::Core::IO::ReadOnlyStream::GetWriteTimeout() const
{
	return _BaseStream.GetWriteTimeout();
}

void Elysium::Core::IO::ReadOnlyStream::SetLength(const size_t Value)
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::ReadOnlyStream::SetPosition(const Elysium::Core::uint64_t Position)
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::ReadOnlyStream::Close()
{
	_BaseStream.Close();
}

void Elysium::Core::IO::ReadOnlyStream::Flush()
{
	throw InvalidOperationException();
}

const size_t Elysium::Core::IO::ReadOnlyStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{
	throw InvalidOperationException();
}

const size_t Elysium::Core::IO::ReadOnlyStream::Read(Elysium::Core::byte* Buffer, const size_t Count)
{
	size_t SupervisedCount = Count;

	if (_BaseStream.GetPosition() != _Position)
	{
		_BaseStream.Seek(_Position, SeekOrigin::Begin);
	}
	if (_Position + SupervisedCount > _End)
	{
		SupervisedCount = _End - _Position;
	}

	const size_t BytesRead = _BaseStream.Read(Buffer, SupervisedCount);

	_Position += BytesRead;

	return BytesRead;
}

Elysium::Core::byte Elysium::Core::IO::ReadOnlyStream::ReadByte()
{	// ToDo
	throw 1;
}

void Elysium::Core::IO::ReadOnlyStream::Write(const Elysium::Core::byte* Buffer, const size_t Count)
{
	throw InvalidOperationException();
}
