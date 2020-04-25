#include "SocketException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Net::Sockets::SocketException::SocketException()
	: Elysium::Core::Runtime::InteropServices::ExternalException(u"SocketException")
{ }
Elysium::Core::Net::Sockets::SocketException::SocketException(String && Message)
	: Elysium::Core::Runtime::InteropServices::ExternalException(std::move(Message))
{ }
Elysium::Core::Net::Sockets::SocketException::SocketException(String && Message, const int ErrorCode)
	: Elysium::Core::Runtime::InteropServices::ExternalException(std::move(Message), ErrorCode)
{ }
Elysium::Core::Net::Sockets::SocketException::~SocketException()
{ }
