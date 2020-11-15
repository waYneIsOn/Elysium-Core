#include "SendReceiveAsyncResult.hpp"

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "Socket.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Net::Sockets::SendReceiveAsyncResult::~SendReceiveAsyncResult()
{ }

const void * Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetAsyncState() const
{
	return _AsyncState;
}

const Elysium::Core::Threading::WaitHandle & Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetAsyncWaitHandle() const
{
	return _OperationDoneEvent;
}

const bool Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetCompletedSynchronously() const
{
	return false;
}

const bool Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetIsCompleted() const
{
	return false;
}

const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*>& Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetCallback() const
{
	return _Callback;
}

const Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetSocket() const
{
	return *_Socket;
}

const Elysium::Core::uint32_t & Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetBytesTransferred() const
{
	return _BytesTransferred;
}

Elysium::Core::Net::Sockets::SendReceiveAsyncResult::SendReceiveAsyncResult(const Elysium::Core::Net::Sockets::Socket * Socket, const Elysium::Core::Delegate<void, const Elysium::Core::IAsyncResult*> & Callback, const void * AsyncState, const size_t BufferSize)
	: Elysium::Core::IAsyncResult(),
	_OperationDoneEvent(false), _Socket(Socket), _Callback(Callback), _AsyncState(AsyncState)
{ }
