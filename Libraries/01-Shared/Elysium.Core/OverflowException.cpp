#include "OverflowException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::OverflowException::OverflowException()
	: Elysium::Core::ArithmeticException(u8"OverflowException")
{ }
Elysium::Core::OverflowException::OverflowException(const char8_t* Message)
	: Elysium::Core::ArithmeticException(Message)
{ }
Elysium::Core::OverflowException::OverflowException(Elysium::Core::String&& Message)
	: Elysium::Core::ArithmeticException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::OverflowException::~OverflowException()
{ }
