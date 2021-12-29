#include "NotSupportedException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::NotSupportedException::NotSupportedException()
	: Elysium::Core::Exception(u8"NotSupportedException")
{ }

Elysium::Core::NotSupportedException::NotSupportedException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }

Elysium::Core::NotSupportedException::NotSupportedException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::NotSupportedException::~NotSupportedException()
{ }
