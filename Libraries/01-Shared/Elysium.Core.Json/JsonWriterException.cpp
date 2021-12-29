#include "JsonWriterException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Json::JsonWriterException::JsonWriterException()
	: Elysium::Core::Json::JsonException()
{ }

Elysium::Core::Json::JsonWriterException::JsonWriterException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Json::JsonException(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Core::Json::JsonWriterException::~JsonWriterException()
{ }
