#include "FileStreamAysncResult.hpp"

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "FileStream.hpp"
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

Elysium::Core::IO::FileStreamAsyncResult::FileStreamAsyncResult(FileStream& Stream, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* AsyncState)
	: _Stream(Stream), _Callback(Callback), _AsyncState(AsyncState), _OperationDoneEvent(false),
	_CompletionPortHandle(CreateThreadpoolIo(_Stream._FileHandle, (PTP_WIN32_IO_CALLBACK)&IOCompletionPortCallback, this,
		&Elysium::Core::Threading::ThreadPool::_IOPool._Environment)),
	_Overlapped()
{
	if (_CompletionPortHandle == nullptr)
	{
		throw IOException();
	}
}

Elysium::Core::IO::FileStreamAsyncResult::~FileStreamAsyncResult()
{
	if (_CompletionPortHandle != nullptr)
	{
		CancelThreadpoolIo(_CompletionPortHandle);
		WaitForThreadpoolIoCallbacks(_CompletionPortHandle, false);
		CloseThreadpoolIo(_CompletionPortHandle);

		_CompletionPortHandle = nullptr;
	}
}

const void* Elysium::Core::IO::FileStreamAsyncResult::GetAsyncState() const
{
	return _AsyncState;
}

const Elysium::Core::Threading::WaitHandle& Elysium::Core::IO::FileStreamAsyncResult::GetAsyncWaitHandle() const
{
	return _OperationDoneEvent;
}

const bool Elysium::Core::IO::FileStreamAsyncResult::GetCompletedSynchronously() const
{
	return false;
}

const bool Elysium::Core::IO::FileStreamAsyncResult::GetIsCompleted() const
{
	return false;
}

const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Elysium::Core::IO::FileStreamAsyncResult::GetCallback() const
{
	return _Callback;
}

Elysium::Core::IO::FileStream& Elysium::Core::IO::FileStreamAsyncResult::GetFileStream() const
{
	return _Stream;
}

void Elysium::Core::IO::FileStreamAsyncResult::IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io)
{
	if (IoResult != NO_ERROR)
	{
		throw IOException(IoResult);
	}

	Elysium::Core::IO::FileStreamAsyncResult* AsyncResult = (Elysium::Core::IO::FileStreamAsyncResult*)Context;
	const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback = AsyncResult->GetCallback();
	Callback(AsyncResult);
}
