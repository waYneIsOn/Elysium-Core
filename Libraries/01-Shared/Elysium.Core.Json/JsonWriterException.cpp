#include "JsonWriterException.hpp"

Elysium::Core::Json::JsonWriterException::JsonWriterException()
	: Elysium::Core::Json::JsonException()
{
}
Elysium::Core::Json::JsonWriterException::JsonWriterException(const String & Message)
	: Elysium::Core::Json::JsonException(Message)
{
}
Elysium::Core::Json::JsonWriterException::~JsonWriterException()
{
}
