#include "JsonException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Json::JsonException::JsonException()
	: Elysium::Core::Exception()
{ }
Elysium::Core::Json::JsonException::JsonException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::Json::JsonException::~JsonException()
{ }
