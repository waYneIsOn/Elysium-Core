#include "SocketException.hpp"

Elysium::Core::Net::Sockets::SocketException::SocketException()
	: Elysium::Core::Runtime::InteropServices::ExternalException(L"SocketException")
{
}
Elysium::Core::Net::Sockets::SocketException::SocketException(const String & Message)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Message)
{
}
Elysium::Core::Net::Sockets::SocketException::SocketException(const String & Message, const int ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Message, ErrorCode)
{
}
Elysium::Core::Net::Sockets::SocketException::~SocketException()
{
}
