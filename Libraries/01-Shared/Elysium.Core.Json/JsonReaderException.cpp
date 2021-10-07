#include "JsonReaderException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Json::JsonReaderException::JsonReaderException()
	: Elysium::Core::Json::JsonException()
{ }
Elysium::Core::Json::JsonReaderException::JsonReaderException(String && Message)
	: Elysium::Core::Json::JsonException(Elysium::Core::Template::Functional::Move(Message))
{ }
Elysium::Core::Json::JsonReaderException::~JsonReaderException()
{ }
