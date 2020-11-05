#include "SocketException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef _INC_COMDEF
#include <comdef.h>
#endif

Elysium::Core::Net::Sockets::SocketException::SocketException()
	: Elysium::Core::Runtime::InteropServices::ExternalException(WSAGetLastError())
{ }
Elysium::Core::Net::Sockets::SocketException::SocketException(const int ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(ErrorCode)
{ }
Elysium::Core::Net::Sockets::SocketException::~SocketException()
{ }

const Elysium::Core::Net::Sockets::SocketError Elysium::Core::Net::Sockets::SocketException::GetSocketError() const
{
	return static_cast<SocketError>(_ErrorCode);
}
