#include "ArgumentOutOfRangeException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException()
	: Elysium::Core::ArgumentException(u8"ArgumentOutOfRangeException")
{ }
Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException(const char8_t* Message)
	: Elysium::Core::ArgumentException(Message)
{ }
Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException(Elysium::Core::String&& Message)
	: Elysium::Core::ArgumentException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::ArgumentOutOfRangeException::~ArgumentOutOfRangeException()
{ }
