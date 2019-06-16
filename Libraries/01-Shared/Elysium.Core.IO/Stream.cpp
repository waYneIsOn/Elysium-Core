#include "Stream.hpp"

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#include "../Elysium.Core/List.hpp"
#endif

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

bool Elysium::Core::IO::Stream::GetCanTimeout() const
{
	return false;
}
int64_t Elysium::Core::IO::Stream::GetPosition() const
{
	if (!GetCanSeek())
	{
		throw NotSupportedException();
	}

	return 0;
}
int Elysium::Core::IO::Stream::GetReadTimeout() const
{
	throw InvalidOperationException();
}
int Elysium::Core::IO::Stream::GetWriteTimeout() const
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::Stream::SetReadTimeout(int Value)
{
	throw InvalidOperationException();
}
void Elysium::Core::IO::Stream::SetWriteTimeout(int Value)
{
	throw InvalidOperationException();
}

void Elysium::Core::IO::Stream::CopyTo(Stream * Destination)
{
	const size_t BufferSize = 4096;
	CopyTo(Destination, BufferSize);
}
void Elysium::Core::IO::Stream::CopyTo(Stream * Destination, const size_t BufferSize)
{
	if (Destination == nullptr)
	{	// ToDo: throw specific ArgumentNullException
#ifdef UNICODE
		throw Exception(L"ArgumentNullException");
#else
		throw Exception("ArgumentNullException");
#endif
	}
	if (BufferSize > INT_MAX)
	{	// ToDo: throw specific ArgumentOutOfRangeException
#ifdef UNICODE
		throw Exception(L"ArgumentOutOfRangeException");
#else
		throw Exception("ArgumentOutOfRangeException");
#endif
	}

	size_t BytesRead = 0;
	Elysium::Core::Collections::Generic::List<Byte> Buffer = Elysium::Core::Collections::Generic::List<Byte>(BufferSize);
	while ((BytesRead = Read(&Buffer[0], BufferSize)) > 0)
	{
		Destination->Write(&Buffer[0], BytesRead);
	}
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
{
}
