#include "InvalidCastException.hpp"

Elysium::Core::InvalidCastException::InvalidCastException()
#ifdef UNICODE
	: Elysium::Core::Exception(L"The specified cast is not valid")
#else
	: Elysium::Core::Exception("The specified cast is not valid")
#endif 
{
}
Elysium::Core::InvalidCastException::InvalidCastException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::InvalidCastException::~InvalidCastException()
{
}
