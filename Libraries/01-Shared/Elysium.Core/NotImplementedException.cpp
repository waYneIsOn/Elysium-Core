#include "NotImplementedException.hpp"

Elysium::Core::NotImplementedException::NotImplementedException()
	: Elysium::Core::Exception(L"NotImplementedException")
{
}
Elysium::Core::NotImplementedException::NotImplementedException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::NotImplementedException::~NotImplementedException()
{
}
