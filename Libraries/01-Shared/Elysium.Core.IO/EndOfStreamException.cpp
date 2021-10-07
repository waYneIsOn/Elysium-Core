#include "EndOfStreamException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::IO::EndOfStreamException::EndOfStreamException()
	: Elysium::Core::IO::IOException(u8"EndOfStreamException")
{ }
Elysium::Core::IO::EndOfStreamException::EndOfStreamException(const char8_t* Message)
	: Elysium::Core::IO::IOException(Message)
{ }
Elysium::Core::IO::EndOfStreamException::EndOfStreamException(String && Message)
	: Elysium::Core::IO::IOException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::IO::EndOfStreamException::~EndOfStreamException()
{ }
