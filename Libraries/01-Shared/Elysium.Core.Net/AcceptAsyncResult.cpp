#include "AcceptAsyncResult.hpp"

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "Socket.hpp"
#endif

Elysium::Core::Net::Sockets::AcceptAsyncResult::AcceptAsyncResult(Elysium::Core::Net::Sockets::Socket& Socket, const Elysium::Core::Container::DelegateOfVoidAtomicIASyncResultReference& Callback, const void* AsyncState, const Elysium::Core::size BufferSize)
	: Elysium::Core::Internal::AsyncResult(Callback, AsyncState, 0x00, nullptr),
	_Socket(Socket), _Addresses{}
{ }

Elysium::Core::Net::Sockets::AcceptAsyncResult::~AcceptAsyncResult()
{ }

Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::AcceptAsyncResult::GetSocket() const
{
	return _Socket;
}