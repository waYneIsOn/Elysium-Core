#include "ArgumentNullException.hpp"

Elysium::Core::ArgumentNullException::ArgumentNullException()
	: Elysium::Core::Exception()
{
}
Elysium::Core::ArgumentNullException::ArgumentNullException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::ArgumentNullException::~ArgumentNullException()
{
}
