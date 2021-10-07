#include "InvalidOperationException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::InvalidOperationException::InvalidOperationException()
	: Elysium::Core::Exception(u8"InvalidOperationException")
{ }
Elysium::Core::InvalidOperationException::InvalidOperationException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::InvalidOperationException::InvalidOperationException(String && Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::InvalidOperationException::~InvalidOperationException()
{ }
