#include "SendReceiveAsyncResult.hpp"

#ifndef ELYSIUM_CORE_NET_SOCKETS_SOCKET
#include "Socket.hpp"
#endif

Elysium::Core::Net::Sockets::SendReceiveAsyncResult::SendReceiveAsyncResult(Elysium::Core::Net::Sockets::Socket& Socket, const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* AsyncState)
	: Elysium::Core::Internal::AsyncResult(Callback, AsyncState, 0x00),
	_Socket(Socket), _WSABuffer()
{ }

Elysium::Core::Net::Sockets::SendReceiveAsyncResult::~SendReceiveAsyncResult()
{ }

Elysium::Core::Net::Sockets::Socket & Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetSocket() const
{
	return _Socket;
}

const Elysium::Core::uint32_t & Elysium::Core::Net::Sockets::SendReceiveAsyncResult::GetBytesTransferred() const
{
	return _BytesTransferred;
}
