#include "AggregateException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::AggregateException::AggregateException()
	: Elysium::Core::Exception(u8"AggregateException")
{ }
Elysium::Core::AggregateException::AggregateException(Elysium::Core::String::ConstCharacterPointer Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::AggregateException::AggregateException(String && Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::AggregateException::~AggregateException()
{ }
