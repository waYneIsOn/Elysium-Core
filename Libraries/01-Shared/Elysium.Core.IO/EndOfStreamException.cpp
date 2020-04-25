#include "EndOfStreamException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::IO::EndOfStreamException::EndOfStreamException()
	: Elysium::Core::IO::IOException(u"EndOfStreamException")
{ }
Elysium::Core::IO::EndOfStreamException::EndOfStreamException(const char16_t * Message)
	: Elysium::Core::IO::IOException(Message)
{ }
Elysium::Core::IO::EndOfStreamException::EndOfStreamException(String && Message)
	: Elysium::Core::IO::IOException(std::move(Message))
{ }
Elysium::Core::IO::EndOfStreamException::~EndOfStreamException()
{ }
