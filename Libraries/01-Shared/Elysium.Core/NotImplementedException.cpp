#include "NotImplementedException.hpp"

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

Elysium::Core::NotImplementedException::NotImplementedException()
	: Elysium::Core::Exception(u"NotImplementedException")
{
}
Elysium::Core::NotImplementedException::NotImplementedException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::NotImplementedException::NotImplementedException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::NotImplementedException::~NotImplementedException()
{
}
