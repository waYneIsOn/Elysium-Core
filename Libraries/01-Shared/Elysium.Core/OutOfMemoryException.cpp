#include "OutOfMemoryException.hpp"

Elysium::Core::OutOfMemoryException::OutOfMemoryException()
	: Elysium::Core::Exception(u"OutOfMemoryException") 
{
}
Elysium::Core::OutOfMemoryException::OutOfMemoryException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::OutOfMemoryException::~OutOfMemoryException()
{
}
