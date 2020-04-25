#include "FileStream.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILENOTFOUNDEXCEPTION
#include "FileNotFoundException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::IO::FileStream::FileStream(const String & Path, const FileMode Mode)
	: FileStream(Path, Mode, FileAccess::ReadWrite, FileShare::None)
{ }
Elysium::Core::IO::FileStream::FileStream(const String & Path, const FileMode Mode, const FileAccess Access)
	: FileStream(Path, Mode, Access, FileShare::None)
{ }
Elysium::Core::IO::FileStream::FileStream(const String& Path, const FileMode Mode, const FileAccess Access, const FileShare Share)
	: Elysium::Core::IO::Stream(), _Path(Path)
{
	int ModeFlag = std::ios::binary;
	int ProtectionFlag = 0;
	
	// ToDo: this is just for testing!!!
	Elysium::Core::Collections::Template::List<byte> ConvertedPath = Elysium::Core::Text::Encoding::Default().GetBytes(_Path.GetCharArray(), 0, _Path.GetLength());
	if (Mode == FileMode::Create)
	{
		_NativeStream.open((char*)&ConvertedPath[0], std::ios::binary | std::ios::out | std::ios::in | std::ios::trunc);
	}
	else
	{
		_NativeStream.open((char*)&ConvertedPath[0], std::ios::binary | std::ios::in);
	}

	if (!_NativeStream.good())
	{
		throw FileNotFoundException();
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

const size_t Elysium::Core::IO::FileStream::GetLength()
{	// ToDo: if the stream position is of the end of the file, this doesn't work!!
	size_t OriginalPosition = _NativeStream.tellg();
	_NativeStream.seekg(0, std::ios::end);
	size_t FileLength = _NativeStream.tellg();
	_NativeStream.seekg(OriginalPosition, std::ios::beg);

	return FileLength;
}
const int64_t Elysium::Core::IO::FileStream::GetPosition()
{
	return _NativeStream.tellg();
}
const int Elysium::Core::IO::FileStream::GetReadTimeout() const
{
	throw NotImplementedException();
}
const int Elysium::Core::IO::FileStream::GetWriteTimeout() const
{
	throw NotImplementedException();
}

void Elysium::Core::IO::FileStream::SetLength(size_t Value)
{
	throw NotImplementedException();
}
void Elysium::Core::IO::FileStream::SetPosition(int64_t Position)
{
	size_t x = GetLength();
	if (Position >= GetLength())
	{	// ToDo: throw specific exception
		throw Exception(u"Position >= FileSize");
	}

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
	throw NotImplementedException();
}
size_t Elysium::Core::IO::FileStream::Read(byte * Buffer, const size_t Count)
{
	if (!_NativeStream.is_open())
	{
		throw NotSupportedException();
	}

	char* CastBuffer = (char*)&Buffer[0];
	_NativeStream.read(CastBuffer, (std::streamsize)Count);
	std::streamsize BytesRead = _NativeStream.gcount();

	return (size_t)BytesRead;
}
int32_t Elysium::Core::IO::FileStream::ReadByte()
{
	byte Buffer;
	char* CastBuffer = (char*)&Buffer;
	_NativeStream.read(CastBuffer, 1);

	return static_cast<int32_t>(Buffer);
}
void Elysium::Core::IO::FileStream::Write(const byte * Buffer, const size_t Count)
{
	if (!_NativeStream.is_open())
	{
		throw NotSupportedException();
	}

	// ToDo: this simple cast doesn't seem right!
	const char* CastBuffer = (const char*)&Buffer[0];
	_NativeStream.write(CastBuffer, Count);
}
