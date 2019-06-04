#include "OutOfMemoryException.hpp"

Elysium::Core::OutOfMemoryException::OutOfMemoryException()
#ifdef UNICODE
	: Elysium::Core::Exception(L"OutOfMemoryException")
#else
	: Elysium::Core::Exception("OutOfMemoryException")
#endif 
{
}
Elysium::Core::OutOfMemoryException::OutOfMemoryException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::OutOfMemoryException::~OutOfMemoryException()
{
}
