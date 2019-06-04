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
int64_t Elysium::Core::IO::Stream::GetPosition() const
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

	return 0;
}
int Elysium::Core::IO::Stream::GetReadTimeout() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw InvalidOperationException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw InvalidOperationException();
#else
#error "undefined os"
#endif
}
int Elysium::Core::IO::Stream::GetWriteTimeout() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw InvalidOperationException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw InvalidOperationException();
#else
#error "undefined os"
#endif
}

void Elysium::Core::IO::Stream::SetReadTimeout(int Value)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw InvalidOperationException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw InvalidOperationException();
#else
#error "undefined os"
#endif
}
void Elysium::Core::IO::Stream::SetWriteTimeout(int Value)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw InvalidOperationException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw InvalidOperationException();
#else
#error "undefined os"
#endif
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
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		throw Exception(L"ArgumentNullException");
#elif defined(__ANDROID__)
		// ToDo: cannot use 'throw' with exceptions disabled
		//throw Exception("ArgumentNullException");
#else
#error "undefined os"
#endif
	}
	if (BufferSize > INT_MAX)
	{	// ToDo: throw specific ArgumentOutOfRangeException
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		throw Exception(L"ArgumentOutOfRangeException");
#elif defined(__ANDROID__)
		// ToDo: cannot use 'throw' with exceptions disabled
		//throw Exception("ArgumentOutOfRangeException");
#else
#error "undefined os"
#endif
	}

	int BytesRead = 0;
	Elysium::Core::Collections::Generic::List<Byte> Buffer = Elysium::Core::Collections::Generic::List<Byte>(BufferSize);
	while ((BytesRead = Read(&Buffer[0], 0, BufferSize)) > 0)
	{
		Destination->Write(&Buffer[0], 0, BytesRead);
	}
}
