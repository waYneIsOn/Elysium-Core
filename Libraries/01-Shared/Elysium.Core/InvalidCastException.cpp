#include "InvalidCastException.hpp"

Elysium::Core::InvalidCastException::InvalidCastException()
	: Elysium::Core::Exception("The specified cast is not valid")
{
}
Elysium::Core::InvalidCastException::InvalidCastException(const char * Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::InvalidCastException::~InvalidCastException()
{
}
