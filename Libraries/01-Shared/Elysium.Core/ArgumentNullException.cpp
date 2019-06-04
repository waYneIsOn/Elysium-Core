#include "ArgumentNullException.hpp"

Elysium::Core::ArgumentNullException::ArgumentNullException()
#ifdef UNICODE
	: Elysium::Core::Exception(L"ArgumentNullException")
#else
	: Elysium::Core::Exception("ArgumentNullException")
#endif 
{
}
Elysium::Core::ArgumentNullException::ArgumentNullException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::ArgumentNullException::~ArgumentNullException()
{
}
