#include "OutOfMemoryException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::OutOfMemoryException::OutOfMemoryException()
	: Elysium::Core::Exception(u8"OutOfMemoryException")
{ }
Elysium::Core::OutOfMemoryException::OutOfMemoryException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::OutOfMemoryException::OutOfMemoryException(Elysium::Core::String&& Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::OutOfMemoryException::~OutOfMemoryException()
{ }
