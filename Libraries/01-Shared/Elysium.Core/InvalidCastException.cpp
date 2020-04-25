#include "InvalidCastException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::InvalidCastException::InvalidCastException()
	: Elysium::Core::Exception(u"The specified cast is not valid")
{ }
Elysium::Core::InvalidCastException::InvalidCastException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::InvalidCastException::InvalidCastException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::InvalidCastException::~InvalidCastException()
{ }
