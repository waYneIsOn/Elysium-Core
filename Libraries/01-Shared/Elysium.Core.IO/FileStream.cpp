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

#ifndef ELYSIUM_CORE_INTERNAL_WRAPPEDOVERLAP
#include "../Elysium.Core/WrappedOverlap.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILENOTFOUNDEXCEPTION
#include "FileNotFoundException.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_THREADPOOL
#include "../Elysium.Core.Threading/ThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_THREADING_INTERNAL_OSTHREADPOOL
#include "../Elysium.Core.Threading/OSThreadPool.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

Elysium::Core::IO::FileStream::FileStream(const char8_t* Path, const FileMode Mode, const FileAccess Access, const FileShare Share, const Elysium::Core::uint32_t BufferSize, const FileOptions Options)
	: Elysium::Core::IO::Stream(), _Path(Path), _Position(0), _FileHandle(CreateNativeFileHandle(_Path, Mode, Access, Share, Options)),
	_CompletionPortHandle(CreateThreadpoolIo(_FileHandle, (PTP_WIN32_IO_CALLBACK)&IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::_IOPool._Environment))
{ }

Elysium::Core::IO::FileStream::FileStream(const Elysium::Core::Utf8String & Path, const FileMode Mode, const FileAccess Access, const FileShare Share, const Elysium::Core::uint32_t BufferSize, const FileOptions Options)
	: Elysium::Core::IO::Stream(), _Path(Path), _Position(0), _FileHandle(CreateNativeFileHandle(_Path, Mode, Access, Share, Options)),
	_CompletionPortHandle(CreateThreadpoolIo(_FileHandle, (PTP_WIN32_IO_CALLBACK)&IOCompletionPortCallback, this, &Elysium::Core::Threading::ThreadPool::_IOPool._Environment))
{ }

Elysium::Core::IO::FileStream::~FileStream()
{
	if (_CompletionPortHandle != nullptr)
	{
		/*
		* It is necessary to wait for any pending io callbacks here or I'm going to cause a memory leak!
		* 
		* Imagine a scenario where in a scope a FileStream gets created on the stack and BeginRead(...) gets called.
		* As soon as the scope ends, the FileStream gets deleted and it's io completion port canceled (due to this very destructor).
		* This means FileStream::IOCompletionPortCallback(...), where the IAsyncResult - created on the heap by BeginRead(...) -
		* would be deleted, is NOT going to be called.
		* Therefore it is also imperative I do not cancel any pending notifications.
		*/
		//CancelThreadpoolIo(_CompletionPortHandle);
		WaitForThreadpoolIoCallbacks(_CompletionPortHandle, FALSE);
		CloseThreadpoolIo(_CompletionPortHandle);

		_CompletionPortHandle = nullptr;
	}
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

const Elysium::Core::size Elysium::Core::IO::FileStream::GetPosition() const
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

	if (Count == 0)
	{
		return;
	}

	Elysium::Core::uint32_t TotalBytesWritten = 0;
	Elysium::Core::uint32_t BytesWritten = 0;
	do
	{
		if (!WriteFile(_FileHandle, &Buffer[TotalBytesWritten], static_cast<unsigned long>(Count - TotalBytesWritten), (unsigned long*)&BytesWritten, nullptr))
		{
			throw IOException();
		}
		TotalBytesWritten += BytesWritten;
		_Position += BytesWritten;
	} while (TotalBytesWritten != Count);
}

Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> Elysium::Core::IO::FileStream::BeginWrite(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State)
{
	if (_CompletionPortHandle == nullptr)
	{	// the file wasn't opened in a way to support io completion ports
		return Stream::BeginWrite(Buffer, Size, Callback, State);
	}
	else
	{
		if (Buffer == nullptr)
		{
			throw ArgumentNullException(u8"Buffer");
		}

		FileStreamAsyncResult* AsyncResult = new FileStreamAsyncResult(*this, Callback, State, 0xFFFFFFFFFFFFFFFF);

		StartThreadpoolIo(_CompletionPortHandle);
		Elysium::Core::int32_t Result = WriteFile(_FileHandle, &Buffer[0], static_cast<DWORD>(Size), 0, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap);
		//Elysium::Core::int32_t Result = WriteFileEx(_FileHandle, &Buffer[0], static_cast<DWORD>(Size), &AsyncResult->_Overlapped, (LPOVERLAPPED_COMPLETION_ROUTINE)nullptr);
		if (!Result)
		{
			Elysium::Core::uint32_t ErrorCode = GetLastError();
			if (ErrorCode != ERROR_IO_PENDING)
			{
				CancelThreadpoolIo(_CompletionPortHandle);
				delete AsyncResult;
				throw IOException();
			}
		}

		return AsyncResult;
	}
}

void Elysium::Core::IO::FileStream::EndWrite(const Elysium::Core::IAsyncResult* AsyncResult)
{
	//const FileStreamAsyncResult* AsyncFileStreamResult = dynamic_cast<const FileStreamAsyncResult*>(AsyncResult);
	FileStreamAsyncResult* AsyncFileStreamResult = (FileStreamAsyncResult*)AsyncResult;
	if (AsyncFileStreamResult == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}

	if (AsyncFileStreamResult->GetErrorCode() != NO_ERROR)
	{
		throw IOException(AsyncFileStreamResult->GetErrorCode());
	}

	Elysium::Core::Threading::ManualResetEvent& AsyncWaitHandle =
		(Elysium::Core::Threading::ManualResetEvent&)AsyncFileStreamResult->GetAsyncWaitHandle();
	bool GetAsyncWaitHandleSetResult = AsyncWaitHandle.Set();

	AsyncFileStreamResult->GetFileStream()._Position += AsyncFileStreamResult->GetBytesTransferred();
}

Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> Elysium::Core::IO::FileStream::BeginRead(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State)
{
	if (Buffer == nullptr)
	{
		throw ArgumentNullException(u8"Buffer");
	}
	
	if (_CompletionPortHandle == nullptr)
	{	// the file wasn't opened in a way to support io completion ports
		return Stream::BeginWrite(Buffer, Size, Callback, State);
	}
	else
	{
		FileStreamAsyncResult* AsyncResult = new FileStreamAsyncResult(*this, Callback, State, _Position);

		StartThreadpoolIo(_CompletionPortHandle);
		Elysium::Core::int32_t Result = ReadFile(_FileHandle, (void*)&Buffer[0], static_cast<DWORD>(Size), nullptr, (LPOVERLAPPED)&AsyncResult->_WrappedOverlap);
		//Elysium::Core::int32_t Result = ReadFileEx(_FileHandle, (void*)&Buffer[0], static_cast<DWORD>(Size), &AsyncResult->_Overlapped, (LPOVERLAPPED_COMPLETION_ROUTINE)nullptr);
		if (!Result)
		{
			Elysium::Core::uint32_t ErrorCode = GetLastError();
			if (ErrorCode != ERROR_IO_PENDING)
			{
				CancelThreadpoolIo(_CompletionPortHandle);
				delete AsyncResult;
				throw IOException();
			}
		}

		return AsyncResult;
	}
}

const Elysium::Core::size Elysium::Core::IO::FileStream::EndRead(const Elysium::Core::IAsyncResult* AsyncResult)
{
	//const FileStreamAsyncResult* AsyncFileStreamResult = dynamic_cast<const FileStreamAsyncResult*>(AsyncResult);
	FileStreamAsyncResult* AsyncFileStreamResult = (FileStreamAsyncResult*)AsyncResult;
	if (AsyncFileStreamResult == nullptr)
	{	// ToDo: throw specific exception
		throw 1;
	}

	if (AsyncFileStreamResult->GetErrorCode() != NO_ERROR)
	{
		throw IOException(AsyncFileStreamResult->GetErrorCode());
	}

	const Elysium::Core::size BytesTransferred = AsyncFileStreamResult->GetBytesTransferred();

	FileStream& TargetStream = AsyncFileStreamResult->GetFileStream();
	TargetStream._Position += BytesTransferred;

	Elysium::Core::Threading::ManualResetEvent& AsyncWaitHandle =
		(Elysium::Core::Threading::ManualResetEvent&)AsyncFileStreamResult->GetAsyncWaitHandle();
	bool GetAsyncWaitHandleSetResult = AsyncWaitHandle.Set();

	return BytesTransferred;
}

#if defined ELYSIUM_CORE_OS_WINDOWS
HANDLE Elysium::Core::IO::FileStream::CreateNativeFileHandle(const Utf8String& Path, const FileMode Mode, const FileAccess Access, const FileShare Share, const FileOptions Options)
{
	HANDLE NativeFileHandle = CreateFile((const wchar_t*)&_OperatingSystemEncoding.GetBytes(&Path[0], Path.GetLength(), sizeof(char16_t))[0],
		static_cast<Elysium::Core::uint32_t>(Access), static_cast<Elysium::Core::uint32_t>(Share),
		nullptr, // default security
		static_cast<Elysium::Core::uint32_t>(Mode), static_cast<Elysium::Core::int32_t>(Options), nullptr);
	//CreateFile2()

	if (NativeFileHandle == INVALID_HANDLE_VALUE)
	{
		throw IOException();
	}

	return NativeFileHandle;
}

void Elysium::Core::IO::FileStream::IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult,
	ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
{
	Elysium::Core::Internal::WrappedOverlap* WrappedOverlap = (Elysium::Core::Internal::WrappedOverlap*)Overlapped;
	Elysium::Core::IAsyncResult* AsyncResult = WrappedOverlap->_AsyncResult;

	Elysium::Core::IO::FileStreamAsyncResult* AsyncFileStreamResult = dynamic_cast<Elysium::Core::IO::FileStreamAsyncResult*>(AsyncResult);
	if (AsyncFileStreamResult != nullptr)
	{
		AsyncFileStreamResult->_BytesTransferred = NumberOfBytesTransferred;
		AsyncFileStreamResult->_ErrorCode = static_cast<Elysium::Core::uint16_t>(IoResult);
		
		const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback = AsyncFileStreamResult->GetCallback();
		Callback(AsyncFileStreamResult);
	}
}
#endif
