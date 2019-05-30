#include "SocketException.hpp"

Elysium::Core::Net::Sockets::SocketException::SocketException()
	: Elysium::Core::Runtime::InteropServices::ExternalException()
{
}
Elysium::Core::Net::Sockets::SocketException::SocketException(char* const Message)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Message)
{
}
Elysium::Core::Net::Sockets::SocketException::SocketException(const char * Message, const int ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(Message, ErrorCode)
{
}
Elysium::Core::Net::Sockets::SocketException::~SocketException()
{
}
