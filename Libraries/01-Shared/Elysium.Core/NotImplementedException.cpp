#include "NotImplementedException.hpp"

Elysium::Core::NotImplementedException::NotImplementedException()
#ifdef UNICODE
	: Elysium::Core::Exception(L"NotImplementedException")
#else
	: Elysium::Core::Exception("NotImplementedException")
#endif 
{
}
Elysium::Core::NotImplementedException::NotImplementedException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::NotImplementedException::~NotImplementedException()
{
}
