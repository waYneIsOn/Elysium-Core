#include "OutOfMemoryException.hpp"

Elysium::Core::OutOfMemoryException::OutOfMemoryException()
	: Elysium::Core::Exception(u"OutOfMemoryException") 
{ }
Elysium::Core::OutOfMemoryException::OutOfMemoryException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::OutOfMemoryException::~OutOfMemoryException()
{ }
