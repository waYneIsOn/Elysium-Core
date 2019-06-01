#include "InvalidCastException.hpp"

Elysium::Core::InvalidCastException::InvalidCastException()
	: Elysium::Core::Exception(L"The specified cast is not valid")
{
}
Elysium::Core::InvalidCastException::InvalidCastException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::InvalidCastException::~InvalidCastException()
{
}
