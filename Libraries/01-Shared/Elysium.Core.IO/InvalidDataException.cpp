#include "InvalidDataException.hpp"

Elysium::Core::IO::InvalidDataException::InvalidDataException()
	: Elysium::Core::Exception(u"InvalidDataException")
{
}
Elysium::Core::IO::InvalidDataException::InvalidDataException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::IO::InvalidDataException::InvalidDataException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::IO::InvalidDataException::~InvalidDataException()
{
}
