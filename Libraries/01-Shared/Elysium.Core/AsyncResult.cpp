#include "AsyncResult.hpp"

#ifndef _THREADPOOLAPISET_H_
#include <threadpoolapiset.h>
#endif

Elysium::Core::Internal::AsyncResult::AsyncResult(const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* AsyncState, const Elysium::Core::size Position, PTP_IO CompletionPortHandle)
	: _Callback(Callback), _AsyncState(AsyncState),
	_OperationDoneEvent(false), _ErrorCode(0), _WrappedOverlap(Position, this),
	_CompletionPortHandle(CompletionPortHandle)
{ }

Elysium::Core::Internal::AsyncResult::~AsyncResult()
{
	if (_CompletionPortHandle != nullptr)
	{
		CancelThreadpoolIo(_CompletionPortHandle);
		_CompletionPortHandle = nullptr;
	}
}

const void* Elysium::Core::Internal::AsyncResult::GetAsyncState() const
{
	return _AsyncState;
}

Elysium::Core::Threading::WaitHandle& Elysium::Core::Internal::AsyncResult::GetAsyncWaitHandle()
{
	return _OperationDoneEvent;
}

const bool Elysium::Core::Internal::AsyncResult::GetCompletedSynchronously() const
{
	throw 1;
}

const bool Elysium::Core::Internal::AsyncResult::GetIsCompleted() const
{
	throw 1;
}

const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Elysium::Core::Internal::AsyncResult::GetCallback() const
{
	return _Callback;
}

const Elysium::Core::uint16_t Elysium::Core::Internal::AsyncResult::GetErrorCode() const
{
	return _ErrorCode;
}

#if defined ELYSIUM_CORE_OS_WINDOWS
const Elysium::Core::Internal::WindowsErrorCode Elysium::Core::Internal::AsyncResult::GetNamedErrorCode() const
{
	return static_cast<Elysium::Core::Internal::WindowsErrorCode>(_ErrorCode);
}
#endif
