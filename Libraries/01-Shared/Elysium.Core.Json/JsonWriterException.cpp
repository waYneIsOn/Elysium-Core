#include "JsonWriterException.hpp"

Elysium::Core::Json::JsonWriterException::JsonWriterException()
	: Elysium::Core::Json::JsonException()
{ }
Elysium::Core::Json::JsonWriterException::JsonWriterException(String && Message)
	: Elysium::Core::Json::JsonException(std::move(Message))
{ }
Elysium::Core::Json::JsonWriterException::~JsonWriterException()
{ }
