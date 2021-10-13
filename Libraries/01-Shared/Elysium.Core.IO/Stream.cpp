#include "Stream.hpp"

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "../Elysium.Core/ArgumentOutOfRangeException.hpp"
#endif

Elysium::Core::IO::Stream::~Stream()
{ }

const bool Elysium::Core::IO::Stream::GetCanTimeout() const
{
	return false;
} 

const Elysium::Core::uint64_t Elysium::Core::IO::Stream::GetPosition() const
{
	if (!GetCanSeek())
	{
		throw NotSupportedException();
	}

	return 0;
}

const Elysium::Core::uint32_t Elysium::Core::IO::Stream::GetReadTimeout() const
{
	throw InvalidOperationException();
}

const Elysium::Core::uint32_t Elysium::Core::IO::Stream::GetWriteTimeout() const
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::Stream::SetReadTimeout(const Elysium::Core::uint32_t Value)
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::Stream::SetWriteTimeout(const Elysium::Core::uint32_t Value)
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::Stream::CopyTo(Stream & Destination)
{
	const Elysium::Core::size BufferSize = 4096;
	CopyTo(Destination, BufferSize);
}

void Elysium::Core::IO::Stream::CopyTo(Stream & Destination, const Elysium::Core::size BufferSize)
{
	if (&Destination == this)
	{
		throw InvalidOperationException(u8"cannot copy from a stream to the same one");
	}

	if (BufferSize > INT_MAX)
	{
		throw ArgumentOutOfRangeException();
	}

	Elysium::Core::size BytesRead = 0;
	Elysium::Core::Collections::Template::List<byte> Buffer = Elysium::Core::Collections::Template::List<byte>(BufferSize);
	while ((BytesRead = Read(&Buffer[0], BufferSize)) > 0)
	{
		Destination.Write(&Buffer[0], BytesRead);
	}
}

void Elysium::Core::IO::Stream::WriteByte(const Elysium::Core::byte Value)
{
	Write(&Value, 1);
}

Elysium::Core::IO::Stream & Elysium::Core::IO::Stream::operator<<(const byte & Value)
{
	Write(&Value, sizeof(Value));
	return (*this);
}

Elysium::Core::IO::Stream & Elysium::Core::IO::Stream::operator<<(const unsigned int & Value)
{
	byte* Bytes = (byte*)&Value;
	Write(Bytes, sizeof(unsigned int));
	return (*this);
}

Elysium::Core::IO::Stream & Elysium::Core::IO::Stream::operator>>(const unsigned int Value)
{
	throw NotImplementedException();

	return (*this);
}

Elysium::Core::IO::Stream::Stream()
{ }
