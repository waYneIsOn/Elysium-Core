#include "NotSupportedException.hpp"

Elysium::Core::NotSupportedException::NotSupportedException()
#ifdef UNICODE
	: Elysium::Core::Exception(L"NotSupportedException")
#else
	: Elysium::Core::Exception("NotSupportedException")
#endif 
{
}
Elysium::Core::NotSupportedException::NotSupportedException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::NotSupportedException::~NotSupportedException()
{
}
