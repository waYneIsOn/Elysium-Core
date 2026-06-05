#include "JsonException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Json::JsonException::JsonException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }

Elysium::Core::Json::JsonException::~JsonException()
{ }
