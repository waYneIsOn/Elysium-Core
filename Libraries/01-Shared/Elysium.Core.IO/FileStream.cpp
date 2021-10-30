#include "FileStream.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "../Elysium.Core/ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "../Elysium.Core/ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTSUPPORTEDEXCEPTION
#include "../Elysium.Core/NotSupportedException.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILENOTFOUNDEXCEPTION
#include "FileNotFoundException.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
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
	: Elysium::Core::IO::Stream(), _Path(Path), _Position(0), _FileHandle(CreateNativeFileHandle(Path, Mode, Access, Share, Options))
{ }

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

const Elysium::Core::size Elysium::Core::IO::FileStream::GetLength() const
{
	LARGE_INTEGER Size;
	if (!GetFileSizeEx(_FileHandle, &Size))
	{
		throw IOException();
	}

	return Size.QuadPart;
}

const Elysium::Core::uint64_t Elysium::Core::IO::FileStream::GetPosition() const
{
	return _Position;
}

const Elysium::Core::uint32_t Elysium::Core::IO::FileStream::GetReadTimeout() const
{
	throw NotImplementedException();
}

const Elysium::Core::uint32_t Elysium::Core::IO::FileStream::GetWriteTimeout() const
{
	throw NotImplementedException();
}

void Elysium::Core::IO::FileStream::SetLength(const Elysium::Core::size Value)
{
	throw NotImplementedException();
}

void Elysium::Core::IO::FileStream::SetPosition(const Elysium::Core::uint64_t Position)
{
	Seek(Position, SeekOrigin::Begin);
}

void Elysium::Core::IO::FileStream::SetReadTimeout(const Elysium::Core::uint32_t Value)
{
	throw NotImplementedException();
}

void Elysium::Core::IO::FileStream::SetWriteTimeout(const Elysium::Core::uint32_t Value)
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
	{
		throw IOException();
	}

	_FileHandle = INVALID_HANDLE_VALUE;
}

void Elysium::Core::IO::FileStream::Flush()
{
	Flush(true);
}

void Elysium::Core::IO::FileStream::Flush(const bool FlushToDisk)
{
	// ToDo: FlushToDisk?
	if (!FlushFileBuffers(_FileHandle))
	{
		throw IOException();
	}
}

const Elysium::Core::size Elysium::Core::IO::FileStream::Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin)
{
	LARGE_INTEGER InternalPosition = LARGE_INTEGER();
	InternalPosition.QuadPart = Offset;

	LARGE_INTEGER NewPosition;

	if (!SetFilePointerEx(_FileHandle, InternalPosition, &NewPosition, static_cast<unsigned long>(Origin)))
	{
		throw IOException();
	}

	_Position = NewPosition.QuadPart;

	return _Position;
}

const Elysium::Core::size Elysium::Core::IO::FileStream::Read(Elysium::Core::byte * Buffer, const Elysium::Core::size Count)
{
	if (Buffer == nullptr)
	{
		throw ArgumentNullException(u8"Buffer");
	}

	Elysium::Core::uint32_t BytesRead = 0;
	if (!ReadFile(_FileHandle, Buffer, static_cast<DWORD>(Count), (unsigned long*)&BytesRead, nullptr))
	{
		throw IOException();
	}
	_Position += BytesRead;

	return BytesRead;
}

Elysium::Core::byte Elysium::Core::IO::FileStream::ReadByte()
{
	Elysium::Core::byte Result = 0x00;
	Read(&Result, 1);

	return Result;
}

void Elysium::Core::IO::FileStream::Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
{
	if (Buffer == nullptr)
	{
		throw ArgumentNullException(u8"Buffer");
	}

	Elysium::Core::uint32_t TotalBytesWritten = 0;
	Elysium::Core::uint32_t BytesWritten = 0;
	do
	{
		if (!WriteFile(_FileHandle, &Buffer[TotalBytesWritten], static_cast<DWORD>(Count - TotalBytesWritten), (unsigned long*)&BytesWritten, nullptr))
		{
			throw IOException();
		}
		TotalBytesWritten += BytesWritten;
		_Position += BytesWritten;
	} while (TotalBytesWritten != Count);

}

const Elysium::Core::IAsyncResult* Elysium::Core::IO::FileStream::BeginWrite(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* State)
{
	if (Buffer == nullptr)
	{
		throw ArgumentNullException(u8"Buffer");
	}

	static unsigned long AppendToEndOfFile = 0xFFFFFFFF;

	FileStreamAsyncResult* AsyncResult = new FileStreamAsyncResult(*this, Callback, State);
	AsyncResult->_Overlapped.Offset = AppendToEndOfFile;
	AsyncResult->_Overlapped.OffsetHigh = AppendToEndOfFile;

	StartThreadpoolIo(AsyncResult->_CompletionPortHandle);
	Elysium::Core::int32_t Result = WriteFile(_FileHandle, &Buffer[0], Size, 0, &AsyncResult->_Overlapped);
	//Elysium::Core::int32_t Result = WriteFileEx(_FileHandle, &Buffer[0], Size, &AsyncResult->_Overlapped, (LPOVERLAPPED_COMPLETION_ROUTINE)nullptr);
	if (!Result)
	{
		Elysium::Core::uint32_t ErrorCode = GetLastError();
		if(ErrorCode != ERROR_IO_PENDING)
		{
			CancelThreadpoolIo(AsyncResult->_CompletionPortHandle);
			delete AsyncResult;
			throw IOException();
		}
	}

	return AsyncResult;
}

void Elysium::Core::IO::FileStream::EndWrite(const Elysium::Core::IAsyncResult* AsyncResult)
{
	/*
	DWORD bytesTransferred;
	unsigned __int64 key;
	LPOVERLAPPED overlappedComp;

	BOOL bSuccess = GetQueuedCompletionStatus(_CompletionPortHandle, &bytesTransferred, &key, &overlappedComp, (DWORD)-1);
	*/
	FileStreamAsyncResult* CastResult = (FileStreamAsyncResult*)AsyncResult;

	//CastResult->_Overlapped

	bool bla = false;
	//return CastResult->_BytesTransferred;
}

#if defined(ELYSIUM_CORE_OS_WINDOWS)
HANDLE Elysium::Core::IO::FileStream::CreateNativeFileHandle(const String& Path, const FileMode Mode, const FileAccess Access, const FileShare Share, const FileOptions Options)
{
	HANDLE NativeFileHandle = CreateFile((const wchar_t*)&_OperatingSystemEncoding.GetBytes(&Path[0], Path.GetLength(), sizeof(char16_t))[0],
		static_cast<Elysium::Core::uint32_t>(Access), static_cast<Elysium::Core::uint32_t>(Share),
		nullptr, // default security
		static_cast<Elysium::Core::uint32_t>(Mode), static_cast<Elysium::Core::int32_t>(Options | FileOptions::Asynchronous), nullptr);
	//CreateFile2()

	if (NativeFileHandle == INVALID_HANDLE_VALUE)
	{
		throw IOException();
	}

	return NativeFileHandle;
}
#endif
