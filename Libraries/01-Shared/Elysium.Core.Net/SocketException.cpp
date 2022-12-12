#include "SocketException.hpp"

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#include <Windows.h>
	#endif
#endif

Elysium::Core::Net::Sockets::SocketException::SocketException()
	: Elysium::Core::Runtime::InteropServices::ExternalException(WSAGetLastError())
{ }

Elysium::Core::Net::Sockets::SocketException::SocketException(const Elysium::Core::int32_t ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(ErrorCode)
{ }

Elysium::Core::Net::Sockets::SocketException::~SocketException()
{ }

const Elysium::Core::Net::Sockets::SocketError Elysium::Core::Net::Sockets::SocketException::GetSocketError() const
{
	return static_cast<SocketError>(_ErrorCode);
}
