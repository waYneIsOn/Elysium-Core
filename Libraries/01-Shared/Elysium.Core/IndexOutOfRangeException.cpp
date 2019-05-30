#include "IndexOutOfRangeException.hpp"

Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException()
	: Elysium::Core::Exception()
{
}
Elysium::Core::IndexOutOfRangeException::IndexOutOfRangeException(const char * Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::IndexOutOfRangeException::~IndexOutOfRangeException()
{
}
