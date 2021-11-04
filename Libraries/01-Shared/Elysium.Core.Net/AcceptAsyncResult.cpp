#include "AcceptAsyncResult.hpp"

Elysium::Core::Net::Sockets::AcceptAsyncResult::AcceptAsyncResult(Elysium::Core::Net::Sockets::Socket& Socket, const Elysium::Core::Delegate<void, const AcceptAsyncResult*>& Callback, const void* AsyncState, const Elysium::Core::size BufferSize)
	: _Socket(Socket), _Callback(Callback), _AsyncState(AsyncState), _OperationDoneEvent(false), _ErrorCode(0),
	_Addresses{}, _Overlapped(), _ClientSocket()
{ }

Elysium::Core::Net::Sockets::AcceptAsyncResult::~AcceptAsyncResult()
{ }

const void * Elysium::Core::Net::Sockets::AcceptAsyncResult::GetAsyncState() const
{
	return _AsyncState;
}

const Elysium::Core::Threading::WaitHandle & Elysium::Core::Net::Sockets::AcceptAsyncResult::GetAsyncWaitHandle() const
{
	return _OperationDoneEvent;
}

const bool Elysium::Core::Net::Sockets::AcceptAsyncResult::GetCompletedSynchronously() const
{
	return false;
}

const bool Elysium::Core::Net::Sockets::AcceptAsyncResult::GetIsCompleted() const
{
	return false;
}

const Elysium::Core::Delegate<void, const Elysium::Core::Net::Sockets::AcceptAsyncResult*>& Elysium::Core::Net::Sockets::AcceptAsyncResult::GetCallback() const
{
	return _Callback;
}

Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::AcceptAsyncResult::GetSocket() const
{
	return _Socket;
}