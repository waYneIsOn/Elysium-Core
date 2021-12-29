#include "InvalidCastException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::InvalidCastException::InvalidCastException()
	: Elysium::Core::Exception(u8"The specified cast is not valid")
{ }

Elysium::Core::InvalidCastException::InvalidCastException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }

Elysium::Core::InvalidCastException::InvalidCastException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::InvalidCastException::~InvalidCastException()
{ }
