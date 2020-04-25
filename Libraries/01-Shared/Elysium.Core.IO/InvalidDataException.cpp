#include "InvalidDataException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::IO::InvalidDataException::InvalidDataException()
	: Elysium::Core::Exception(u"InvalidDataException")
{ }
Elysium::Core::IO::InvalidDataException::InvalidDataException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::IO::InvalidDataException::InvalidDataException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::IO::InvalidDataException::~InvalidDataException()
{ }
