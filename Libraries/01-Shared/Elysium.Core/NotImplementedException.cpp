#include "NotImplementedException.hpp"

Elysium::Core::NotImplementedException::NotImplementedException()
	: Elysium::Core::Exception()
{
}
Elysium::Core::NotImplementedException::NotImplementedException(const char * Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::NotImplementedException::~NotImplementedException()
{
}
