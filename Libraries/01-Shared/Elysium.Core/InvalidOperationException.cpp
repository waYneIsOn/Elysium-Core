#include "InvalidOperationException.hpp"

Elysium::Core::InvalidOperationException::InvalidOperationException()
#ifdef UNICODE
	: Elysium::Core::Exception(L"InvalidOperationException")
#else
	: Elysium::Core::Exception("InvalidOperationException")
#endif 
{
}
Elysium::Core::InvalidOperationException::InvalidOperationException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::InvalidOperationException::~InvalidOperationException()
{
}
