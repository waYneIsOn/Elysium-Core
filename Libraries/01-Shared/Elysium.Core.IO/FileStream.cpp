#include "FileStream.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILENOTFOUNDEXCEPTION
#include "FileNotFoundException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "ArgumentOutOfRangeException.hpp"
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
	: FileStream(Path, Mode, Access, Share, DefaultBufferSize, FileOptions::None)
{ }
Elysium::Core::IO::FileStream::FileStream(const String& Path, const FileMode Mode, const FileAccess Access, const FileShare Share, const Elysium::Core::uint32_t BufferSize, const FileOptions Options)
	: Elysium::Core::IO::Stream(),
	_Path(Path), _FileHandle(CreateFile((const wchar_t*)&_WindowsEncoding.GetBytes(&Path[0], Path.GetLength(), sizeof(wchar_t))[0],
		static_cast<Elysium::Core::uint32_t>(Access), static_cast<Elysium::Core::uint32_t>(Share), 
		nullptr, // default security
		static_cast<Elysium::Core::uint32_t>(Mode), static_cast<Elysium::Core::int32_t>(Options), nullptr))
{
	if (_FileHandle == INVALID_HANDLE_VALUE)
	{	// ToDo: check values to throw specific exceptions
		throw NotImplementedException();
	}
}
Elysium::Core::IO::FileStream::~FileStream()
{
	Close();
}

const bool Elysium::Core::IO::FileStream::GetCanRead() const
{
	throw NotImplementedException();
	//return _Access | FileAccess::Read || _Access | FileAccess::ReadWrite;
}

const bool Elysium::Core::IO::FileStream::GetCanSeek() const
{
	throw NotImplementedException();
}

const bool Elysium::Core::IO::FileStream::GetCanTimeout() const
{
	throw NotImplementedException();
}

const bool Elysium::Core::IO::FileStream::GetCanWrite() const
{
	throw NotImplementedException();
}

const size_t Elysium::Core::IO::FileStream::GetLength() const
{
	LARGE_INTEGER Size;
	if (!GetFileSizeEx(_FileHandle, &Size))
	{	// ToDo: throw according exception
		throw 1;
	}

	// ToDo: return the correct value
	//return Size.QuadPart;
	throw 1;
}

const Elysium::Core::int64_t Elysium::Core::IO::FileStream::GetPosition() const
{
	//return _NativeStream.tellg();
	throw NotImplementedException();
}

const Elysium::Core::int32_t Elysium::Core::IO::FileStream::GetReadTimeout() const
{
	throw NotImplementedException();
}

const Elysium::Core::int32_t Elysium::Core::IO::FileStream::GetWriteTimeout() const
{
	throw NotImplementedException();
}

void Elysium::Core::IO::FileStream::SetLength(const size_t Value)
{
	throw NotImplementedException();
}

void Elysium::Core::IO::FileStream::SetPosition(const Elysium::Core::int64_t Position)
{
	throw NotImplementedException();
	/*
	if (Position >= GetLength())
	{	// ToDo: throw specific exception
		throw Exception(u8"Position >= FileSize");
	}

	_NativeStream.clear();	// required call (resets internal error state flags)
	_NativeStream.seekg((std::streampos)Position, std::ios::beg);
	*/
}

void Elysium::Core::IO::FileStream::SetReadTimeout(const Elysium::Core::int32_t Value)
{
	throw NotImplementedException();
}

void Elysium::Core::IO::FileStream::SetWriteTimeout(const Elysium::Core::int32_t Value)
{
	throw NotImplementedException();
}

void Elysium::Core::IO::FileStream::Close()
{
	if (_FileHandle == INVALID_HANDLE_VALUE)
	{
		return;
	}
	
	if (!CloseHandle(_FileHandle))
	{	// ToDo: throw specific exception
		throw NotImplementedException();
	}

	_FileHandle = INVALID_HANDLE_VALUE;
}

void Elysium::Core::IO::FileStream::Flush()
{
	Flush(true);
}

void Elysium::Core::IO::FileStream::Flush(const bool FlushToDisk)
{
	if (!FlushFileBuffers(_FileHandle))
	{	// ToDo: throw specific exception
		throw NotImplementedException();
	}
}

void Elysium::Core::IO::FileStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{
	throw NotImplementedException();
}

const size_t Elysium::Core::IO::FileStream::Read(Elysium::Core::byte * Buffer, const size_t Count)
{
	throw NotImplementedException();
	/*
	char* CastBuffer = (char*)&Buffer[0];
	_NativeStream.read(CastBuffer, (std::streamsize)Count);
	std::streamsize BytesRead = _NativeStream.gcount();

	return (size_t)BytesRead;
	*/
}

Elysium::Core::byte Elysium::Core::IO::FileStream::ReadByte()
{
	throw NotImplementedException();
	/*
	byte Buffer;
	char* CastBuffer = (char*)&Buffer;
	_NativeStream.read(CastBuffer, 1);

	return static_cast<int32_t>(Buffer);
	*/
}

void Elysium::Core::IO::FileStream::Write(const Elysium::Core::byte* Buffer, const size_t Count)
{
	if (_FileHandle == INVALID_HANDLE_VALUE)
	{	// ToDo: check values to throw specific exceptions
		throw NotImplementedException();
	}


	throw NotImplementedException();
	/*
	if (!_NativeStream.is_open())
	{
		throw NotSupportedException();
	}

	// ToDo: this simple cast doesn't seem right!
	const char* CastBuffer = (const char*)&Buffer[0];
	_NativeStream.write(CastBuffer, Count);
	*/
}
