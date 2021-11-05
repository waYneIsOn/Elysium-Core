#include "SemaphoreFullException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Threading::SemaphoreFullException::SemaphoreFullException()
	: Elysium::Core::Exception(u8"SemaphoreFullException")
{ }

Elysium::Core::Threading::SemaphoreFullException::SemaphoreFullException(String && Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::Threading::SemaphoreFullException::~SemaphoreFullException()
{ }
