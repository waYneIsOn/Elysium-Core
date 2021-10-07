#include "IndexOutOfRangeException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException()
	: Elysium::Core::Exception(u8"IndexOutOfRangeException")
{ }
Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException(Elysium::Core::String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::IndexOutOfRangeException::~IndexOutOfRangeException()
{ }
