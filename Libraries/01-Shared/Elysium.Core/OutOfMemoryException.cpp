#include "OutOfMemoryException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::OutOfMemoryException::OutOfMemoryException()
	: Elysium::Core::Exception(u"OutOfMemoryException")
{ }
Elysium::Core::OutOfMemoryException::OutOfMemoryException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::OutOfMemoryException::OutOfMemoryException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::OutOfMemoryException::~OutOfMemoryException()
{ }
