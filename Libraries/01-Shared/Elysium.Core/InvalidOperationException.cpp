#include "InvalidOperationException.hpp"

Elysium::Core::InvalidOperationException::InvalidOperationException()
	: Elysium::Core::Exception(u"InvalidOperationException")
{
}
Elysium::Core::InvalidOperationException::InvalidOperationException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::InvalidOperationException::InvalidOperationException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::InvalidOperationException::~InvalidOperationException()
{
}
