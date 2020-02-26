#include "AggregateException.hpp"

Elysium::Core::AggregateException::AggregateException()
	: Elysium::Core::Exception(u"AggregateException")
{ }
Elysium::Core::AggregateException::AggregateException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::AggregateException::~AggregateException()
{ }
