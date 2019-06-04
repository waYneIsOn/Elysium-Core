#include "FileStream.hpp"

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::IO::FileStream::FileStream(std::wstring Path, FileMode Mode, FileAccess Access, FileShare Share)
	: Elysium::Core::IO::Stream(),
	_Path(Path), _Mode(Mode), _Access(Access), _Share(Share)
{
	// ToDo: this is just for testing!!!
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	if (Mode == FileMode::Create)
	{
		_NativeStream.open(_Path, std::fstream::binary | std::ios::out | std::ios::in | std::ios::trunc);
	}
	else
	{
		_NativeStream.open(_Path, std::fstream::binary | std::ios::out | std::ios::in);
	}
#elif defined(__ANDROID__)
	// ToDo:
#else
#error "undefined os"
#endif
}
Elysium::Core::IO::FileStream::~FileStream()
{
	Close();
}

bool Elysium::Core::IO::FileStream::GetCanRead() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
	//return _Access | FileAccess::Read || _Access | FileAccess::ReadWrite;
}
bool Elysium::Core::IO::FileStream::GetCanSeek() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}
bool Elysium::Core::IO::FileStream::GetCanTimeout() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}
bool Elysium::Core::IO::FileStream::GetCanWrite() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}

size_t Elysium::Core::IO::FileStream::GetLength() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}
int64_t Elysium::Core::IO::FileStream::GetPosition() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}
int Elysium::Core::IO::FileStream::GetReadTimeout() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}
int Elysium::Core::IO::FileStream::GetWriteTimeout() const
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}

void Elysium::Core::IO::FileStream::SetLength(size_t Value)
{
}
void Elysium::Core::IO::FileStream::SetPosition(int64_t Position)
{
	_NativeStream.clear();	// required call (resets internal error state flags)
	_NativeStream.seekg((std::streampos)Position, std::ios::beg);
}
void Elysium::Core::IO::FileStream::SetReadTimeout(int Value)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}
void Elysium::Core::IO::FileStream::SetWriteTimeout(int Value)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	throw NotImplementedException();
#elif defined(__ANDROID__)
	// ToDo: cannot use 'throw' with exceptions disabled
	//throw NotImplementedException();
#else
#error "undefined os"
#endif
}

void Elysium::Core::IO::FileStream::Close()
{
	_NativeStream.close();
}
void Elysium::Core::IO::FileStream::Flush()
{
	_NativeStream.flush();
}
void Elysium::Core::IO::FileStream::Seek(const int64_t Offset, const SeekOrigin Origin)
{
}
int Elysium::Core::IO::FileStream::Read(byte * Buffer, int Offset, int Count)
{
	if (!_NativeStream.is_open())
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

	// ToDo: this simple cast doesn't seem right!
	char* CastBuffer = (char*)&Buffer[Offset];
	_NativeStream.read(CastBuffer, (std::streamsize)Count);
	std::streamsize BytesReceived = _NativeStream.gcount();

	return (int)BytesReceived;
}
void Elysium::Core::IO::FileStream::Write(const byte * Buffer, int Offset, int Count)
{
	if (!_NativeStream.is_open())
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

	// ToDo: this simple cast doesn't seem right!
	const char* CastBuffer = (const char*)&Buffer[0];
	_NativeStream.write(CastBuffer, Count);
}
