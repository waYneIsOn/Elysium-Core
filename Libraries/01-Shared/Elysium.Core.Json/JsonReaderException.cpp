#include "JsonReaderException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Json::JsonReaderException::JsonReaderException(const char8_t* Message)
	: Elysium::Core::Json::JsonException(Message)
{ }

Elysium::Core::Json::JsonReaderException::~JsonReaderException()
{ }
