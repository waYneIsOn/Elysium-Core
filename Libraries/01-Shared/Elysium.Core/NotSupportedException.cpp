#include "NotSupportedException.hpp"

Elysium::Core::NotSupportedException::NotSupportedException()
	: Elysium::Core::Exception(u"NotSupportedException")
{
}
Elysium::Core::NotSupportedException::NotSupportedException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::NotSupportedException::~NotSupportedException()
{
}
