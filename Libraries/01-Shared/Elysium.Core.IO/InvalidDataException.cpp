#include "InvalidDataException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IO::InvalidDataException::InvalidDataException()
	: Elysium::Core::Exception(u8"InvalidDataException")
{ }

Elysium::Core::IO::InvalidDataException::InvalidDataException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }

Elysium::Core::IO::InvalidDataException::InvalidDataException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::IO::InvalidDataException::~InvalidDataException()
{ }
