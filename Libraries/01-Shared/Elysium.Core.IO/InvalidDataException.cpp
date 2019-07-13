#include "InvalidDataException.hpp"

Elysium::Core::IO::InvalidDataException::InvalidDataException()
#ifdef UNICODE
	: Elysium::Core::Exception(L"InvalidDataException")
#else
	: Elysium::Core::Exception("InvalidDataException")
#endif 
{
}
Elysium::Core::IO::InvalidDataException::InvalidDataException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::IO::InvalidDataException::~InvalidDataException()
{
}
