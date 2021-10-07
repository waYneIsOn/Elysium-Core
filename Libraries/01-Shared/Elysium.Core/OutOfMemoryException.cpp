#include "OutOfMemoryException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::OutOfMemoryException::OutOfMemoryException()
	: Elysium::Core::Exception(u8"OutOfMemoryException")
{ }
Elysium::Core::OutOfMemoryException::OutOfMemoryException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::OutOfMemoryException::OutOfMemoryException(Elysium::Core::String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::OutOfMemoryException::~OutOfMemoryException()
{ }
