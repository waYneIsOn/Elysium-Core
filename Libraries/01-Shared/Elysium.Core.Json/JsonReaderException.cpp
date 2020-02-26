#include "JsonReaderException.hpp"

Elysium::Core::Json::JsonReaderException::JsonReaderException()
	: Elysium::Core::Json::JsonException()
{ }
Elysium::Core::Json::JsonReaderException::JsonReaderException(String && Message)
	: Elysium::Core::Json::JsonException(std::move(Message))
{ }
Elysium::Core::Json::JsonReaderException::~JsonReaderException()
{ }
