#include "NotSupportedException.hpp"

Elysium::Core::NotSupportedException::NotSupportedException()
	: Elysium::Core::Exception()
{
}
Elysium::Core::NotSupportedException::NotSupportedException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::NotSupportedException::~NotSupportedException()
{
}
