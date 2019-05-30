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

Elysium::Core::IO::Stream::Stream()
{
}

bool Elysium::Core::IO::Stream::GetCanTimeout() const
{
	return false;
}
__int64 Elysium::Core::IO::Stream::GetPosition() const
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
		throw Exception("ArgumentNullException");
	}
	if (BufferSize > INT_MAX)
	{	// ToDo: throw specific ArgumentOutOfRangeException
		throw Exception("ArgumentOutOfRangeException");
	}

	int BytesRead = 0;
	Elysium::Core::Collections::Generic::List<Byte> Buffer = Elysium::Core::Collections::Generic::List<Byte>(BufferSize);
	while ((BytesRead = Read(&Buffer[0], 0, BufferSize)) > 0)
	{
		Destination->Write(&Buffer[0], 0, BytesRead);
	}
}
