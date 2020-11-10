#include "SendReceiveAsyncResult.hpp"

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "Socket.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Net::Sockets::SendReceiveAsyncResult::~SendReceiveAsyncResult()
{ }

const Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetSocket() const
{
	return *_Socket;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetBuffer() const
{
	return _Buffer;
}

const void * Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetAsyncState() const
{
	return _AsyncState;
}

const Elysium::Core::Threading::WaitHandle & Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetAsyncWaitHandle() const
{
	throw 1;
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

Elysium::Core::Net::Sockets::SendReceiveAsyncResult::SendReceiveAsyncResult(const Elysium::Core::Net::Sockets::Socket * Socket, const Elysium::Core::Delegate<void, const IAsyncResult*> & Callback, const void * AsyncState, const size_t BufferSize)
	: Elysium::Core::IAsyncResult(),
	_Socket(Socket), _Callback(Callback), _AsyncState(AsyncState), _Buffer(BufferSize)
{ }
