#include "JsonReaderException.hpp"

Elysium::Core::Json::JsonReaderException::JsonReaderException()
	: Elysium::Core::Json::JsonException()
{
}
Elysium::Core::Json::JsonReaderException::JsonReaderException(const String & Message)
	: Elysium::Core::Json::JsonException(Message)
{
}
Elysium::Core::Json::JsonReaderException::~JsonReaderException()
{
}
