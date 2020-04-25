#include "AggregateException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::AggregateException::AggregateException()
	: Elysium::Core::Exception(u"AggregateException")
{ }
Elysium::Core::AggregateException::AggregateException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::AggregateException::AggregateException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::AggregateException::~AggregateException()
{ }
