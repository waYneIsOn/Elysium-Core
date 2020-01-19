#include "SemaphoreFullException.hpp"

Elysium::Core::Threading::SemaphoreFullException::SemaphoreFullException()
	: Elysium::Core::Exception(u"")
{
}
Elysium::Core::Threading::SemaphoreFullException::SemaphoreFullException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::Threading::SemaphoreFullException::~SemaphoreFullException()
{
}
