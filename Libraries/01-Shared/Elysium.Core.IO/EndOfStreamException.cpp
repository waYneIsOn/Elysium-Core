#include "EndOfStreamException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::IO::EndOfStreamException::EndOfStreamException()
	: Elysium::Core::IO::IOException(u8"EndOfStreamException")
{ }
Elysium::Core::IO::EndOfStreamException::EndOfStreamException(const char * Message)
	: Elysium::Core::IO::IOException(Message)
{ }
Elysium::Core::IO::EndOfStreamException::EndOfStreamException(String && Message)
	: Elysium::Core::IO::IOException(std::move(Message))
{ }
Elysium::Core::IO::EndOfStreamException::~EndOfStreamException()
{ }
