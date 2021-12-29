#include "ArgumentNullException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::ArgumentNullException::ArgumentNullException()
	: Elysium::Core::ArgumentException(u8"ArgumentNullException")
{ }

Elysium::Core::ArgumentNullException::ArgumentNullException(const char8_t* Message)
	: Elysium::Core::ArgumentException(Message)
{ }

Elysium::Core::ArgumentNullException::ArgumentNullException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::ArgumentException(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::ArgumentNullException::~ArgumentNullException()
{ }
