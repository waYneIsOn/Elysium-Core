#include "ArgumentException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::ArgumentException::ArgumentException()
	: Elysium::Core::SystemException(u8"ArgumentException")
{ }
Elysium::Core::ArgumentException::ArgumentException(const char8_t* Message)
	: Elysium::Core::SystemException(Message)
{ }
Elysium::Core::ArgumentException::ArgumentException(String && Message)
	: Elysium::Core::SystemException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::ArgumentException::~ArgumentException()
{ }
