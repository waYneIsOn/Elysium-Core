#include "NotImplementedException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::NotImplementedException::NotImplementedException()
	: Elysium::Core::Exception(u8"NotImplementedException")
{ }
Elysium::Core::NotImplementedException::NotImplementedException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::NotImplementedException::NotImplementedException(Elysium::Core::String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::NotImplementedException::~NotImplementedException()
{ }
