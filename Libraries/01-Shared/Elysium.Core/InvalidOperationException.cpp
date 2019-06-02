#include "InvalidOperationException.hpp"

Elysium::Core::InvalidOperationException::InvalidOperationException()
	: Elysium::Core::Exception(L"InvalidOperationException")
{
}
Elysium::Core::InvalidOperationException::InvalidOperationException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::InvalidOperationException::~InvalidOperationException()
{
}
