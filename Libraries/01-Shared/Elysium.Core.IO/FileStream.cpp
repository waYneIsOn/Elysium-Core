#include "FileStream.hpp"

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::IO::FileStream::FileStream(const String& Path, FileMode Mode, FileAccess Access, FileShare Share)
	: Elysium::Core::IO::Stream(),
	_Path(Path), _Mode(Mode), _Access(Access), _Share(Share)
{
	// ToDo: this is just for testing!!!
	if (Mode == FileMode::Create)
	{
		_NativeStream.open(_Path.GetCharArray(), std::fstream::binary | std::ios::out | std::ios::in | std::ios::trunc);
	}
	else
	{
		_NativeStream.open(_Path.GetCharArray(), std::fstream::binary | std::ios::out | std::ios::in);
	}
}
Elysium::Core::IO::FileStream::~FileStream()
{
	Close();
}

bool Elysium::Core::IO::FileStream::GetCanRead() const
{
	throw NotImplementedException();
	//return _Access | FileAccess::Read || _Access | FileAccess::ReadWrite;
}
bool Elysium::Core::IO::FileStream::GetCanSeek() const
{
	throw NotImplementedException();
}
bool Elysium::Core::IO::FileStream::GetCanTimeout() const
{
	throw NotImplementedException();
}
bool Elysium::Core::IO::FileStream::GetCanWrite() const
{
	throw NotImplementedException();
}

size_t Elysium::Core::IO::FileStream::GetLength() const
{
	throw NotImplementedException();
}
int64_t Elysium::Core::IO::FileStream::GetPosition() const
{
	throw NotImplementedException();
}
int Elysium::Core::IO::FileStream::GetReadTimeout() const
{
	throw NotImplementedException();
}
int Elysium::Core::IO::FileStream::GetWriteTimeout() const
{
	throw NotImplementedException();
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
	throw NotImplementedException();
}
void Elysium::Core::IO::FileStream::SetWriteTimeout(int Value)
{
	throw NotImplementedException();
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
size_t Elysium::Core::IO::FileStream::Read(byte * Buffer, const size_t Offset, const size_t Count)
{
	if (!_NativeStream.is_open())
	{
		throw NotSupportedException();
	}

	// ToDo: this simple cast doesn't seem right!
	char* CastBuffer = (char*)&Buffer[Offset];
	_NativeStream.read(CastBuffer, (std::streamsize)Count);
	std::streamsize BytesReceived = _NativeStream.gcount();

	return (size_t)BytesReceived;
}
void Elysium::Core::IO::FileStream::Write(const byte * Buffer, const size_t Offset, const size_t Count)
{
	if (!_NativeStream.is_open())
	{
		throw NotSupportedException();
	}

	// ToDo: this simple cast doesn't seem right!
	const char* CastBuffer = (const char*)&Buffer[0];
	_NativeStream.write(CastBuffer, Count);
}
