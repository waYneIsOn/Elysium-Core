#include "IndexOutOfRangeException.hpp"

Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException()
#ifdef UNICODE
	: Elysium::Core::Exception(L"IndexOutOfRangeException")
#else
	: Elysium::Core::Exception("IndexOutOfRangeException")
#endif 
{
}
Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::IndexOutOfRangeException::~IndexOutOfRangeException()
{
}
