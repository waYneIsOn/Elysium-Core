#include "DivideByZeroException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::DivideByZeroException::DivideByZeroException()
	: Elysium::Core::ArithmeticException(u8"DivideByZeroException")
{ }
Elysium::Core::DivideByZeroException::DivideByZeroException(const char8_t* Message)
	: Elysium::Core::ArithmeticException(Message)
{ }
Elysium::Core::DivideByZeroException::DivideByZeroException(Elysium::Core::String&& Message)
	: Elysium::Core::ArithmeticException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::DivideByZeroException::~DivideByZeroException()
{ }
