#include "JsonException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Json::JsonException::JsonException()
	: Elysium::Core::Exception()
{ }

Elysium::Core::Json::JsonException::JsonException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::Json::JsonException::~JsonException()
{ }
