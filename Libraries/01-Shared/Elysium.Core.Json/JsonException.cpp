#include "JsonException.hpp"

Elysium::Core::Json::JsonException::JsonException()
	: Elysium::Core::Exception()
{ }
Elysium::Core::Json::JsonException::JsonException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::Json::JsonException::~JsonException()
{ }
