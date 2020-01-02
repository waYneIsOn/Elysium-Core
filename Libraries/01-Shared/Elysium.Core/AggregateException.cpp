#include "AggregateException.hpp"

Elysium::Core::AggregateException::AggregateException()
	: Elysium::Core::Exception(u"AggregateException")
{
}
Elysium::Core::AggregateException::AggregateException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::AggregateException::~AggregateException()
{
}
