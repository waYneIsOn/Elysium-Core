#include "AsyncResult.hpp"

Elysium::Core::Internal::AsyncResult::AsyncResult(const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Callback, const void* AsyncState, const Elysium::Core::size Position)
	: _Callback(Callback), _AsyncState(AsyncState),
	_OperationDoneEvent(false), _ErrorCode(0), _WrappedOverlap(Position, this)
{ }

Elysium::Core::Internal::AsyncResult::~AsyncResult()
{ }

const void* Elysium::Core::Internal::AsyncResult::GetAsyncState() const
{
	return _AsyncState;
}

const Elysium::Core::Threading::WaitHandle& Elysium::Core::Internal::AsyncResult::GetAsyncWaitHandle() const
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

const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Elysium::Core::Internal::AsyncResult::GetCallback() const
{
	return _Callback;
}

const Elysium::Core::uint16_t Elysium::Core::Internal::AsyncResult::GetErrorCode() const
{
	return _ErrorCode;
}

const Elysium::Core::Internal::WindowsErrorCode Elysium::Core::Internal::AsyncResult::GetNamedErrorCode() const
{
	return static_cast<Elysium::Core::Internal::WindowsErrorCode>(_ErrorCode);
}
