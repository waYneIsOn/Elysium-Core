#include "InvalidCastException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::InvalidCastException::InvalidCastException()
	: Elysium::Core::Exception(u8"The specified cast is not valid")
{ }
Elysium::Core::InvalidCastException::InvalidCastException(const char * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::InvalidCastException::InvalidCastException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::InvalidCastException::~InvalidCastException()
{ }
