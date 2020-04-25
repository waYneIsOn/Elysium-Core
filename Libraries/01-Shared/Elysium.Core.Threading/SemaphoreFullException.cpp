#include "SemaphoreFullException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Threading::SemaphoreFullException::SemaphoreFullException()
	: Elysium::Core::Exception(u"")
{ }
Elysium::Core::Threading::SemaphoreFullException::SemaphoreFullException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::Threading::SemaphoreFullException::~SemaphoreFullException()
{ }
