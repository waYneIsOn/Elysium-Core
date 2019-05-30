#include "InvalidOperationException.hpp"

Elysium::Core::InvalidOperationException::InvalidOperationException()
	: Elysium::Core::Exception()
{
}
Elysium::Core::InvalidOperationException::InvalidOperationException(const char * Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::InvalidOperationException::~InvalidOperationException()
{
}
