#include "ArithmeticException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::ArithmeticException::ArithmeticException()
	: Elysium::Core::SystemException(u8"ArgumentNullException")
{ }
Elysium::Core::ArithmeticException::ArithmeticException(const char8_t* Message)
	: Elysium::Core::SystemException(Message)
{ }
Elysium::Core::ArithmeticException::ArithmeticException(Elysium::Core::String&& Message)
	: Elysium::Core::SystemException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::ArithmeticException::~ArithmeticException()
{ }
