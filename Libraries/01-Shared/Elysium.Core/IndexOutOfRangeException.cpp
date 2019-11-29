#include "IndexOutOfRangeException.hpp"

Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException()
	: Elysium::Core::Exception(u"IndexOutOfRangeException")
{
}
Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::IndexOutOfRangeException::~IndexOutOfRangeException()
{
}
