#include "FileStreamAysncResult.hpp"

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "FileStream.hpp"
#endif

Elysium::Core::IO::FileStreamAsyncResult::FileStreamAsyncResult(FileStream& Stream, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* AsyncState)
	: _Stream(Stream), _Callback(Callback), _AsyncState(AsyncState), _OperationDoneEvent(false), _BytesTransferred(0), _ErrorCode(0),
	_Overlapped()
{ }

Elysium::Core::IO::FileStreamAsyncResult::~FileStreamAsyncResult()
{ }

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

const Elysium::Core::size Elysium::Core::IO::FileStreamAsyncResult::GetBytesTransferred() const
{
	return _BytesTransferred;
}

const Elysium::Core::uint16_t Elysium::Core::IO::FileStreamAsyncResult::GetErrorCode() const
{
	return _ErrorCode;
}

#if defined(ELYSIUM_CORE_OS_WINDOWS)
const Elysium::Core::Internal::WindowsErrorCode Elysium::Core::IO::FileStreamAsyncResult::GetNamedErrorCode() const
{
	return static_cast<Elysium::Core::Internal::WindowsErrorCode>(_ErrorCode);
}
#endif
