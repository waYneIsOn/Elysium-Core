#include "JsonException.hpp"

Elysium::Core::Json::JsonException::JsonException()
	: Elysium::Core::Exception()
{
}
Elysium::Core::Json::JsonException::JsonException(const String & Message)
	: Elysium::Core::Exception(Message)
{
}
Elysium::Core::Json::JsonException::~JsonException()
{
}
