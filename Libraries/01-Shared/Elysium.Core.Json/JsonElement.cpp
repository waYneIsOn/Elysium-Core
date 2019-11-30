#include "JsonElement.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../Elysium.Core/InvalidOperationException.hpp"
#endif

Elysium::Core::Json::JsonElement::JsonElement(const String & Name, const String & Value)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name), _Type(JsonNodeType::String), _Value(Value)
{
}
Elysium::Core::Json::JsonElement::JsonElement(const String & Name, const int32_t Value)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name), _Type(JsonNodeType::Integer), _Value(Value)
{
}
Elysium::Core::Json::JsonElement::JsonElement(const String & Name, const float Value)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name), _Type(JsonNodeType::Float), _Value(Value)
{
}
Elysium::Core::Json::JsonElement::JsonElement(const String & Name, const double Value)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name), _Type(JsonNodeType::Double), _Value(Value)
{
}
Elysium::Core::Json::JsonElement::JsonElement(const String & Name, const bool Value)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name), _Type(JsonNodeType::Boolean), _Value(Value)
{
}
Elysium::Core::Json::JsonElement::JsonElement(const String & Name, const void * Value)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name), _Type(JsonNodeType::Null), _Value()
{
}
Elysium::Core::Json::JsonElement::~JsonElement()
{
}

const Elysium::Core::String & Elysium::Core::Json::JsonElement::GetName() const
{
	return _Name;
}
const Elysium::Core::Json::JsonNodeType Elysium::Core::Json::JsonElement::GetNodeType() const
{
	return _Type;
}

const Elysium::Core::String & Elysium::Core::Json::JsonElement::GetValueAsString() const
{
	if (_Type != JsonNodeType::String)
	{
		throw InvalidOperationException();
	}
	return std::get<String>(_Value);
}

void Elysium::Core::Json::JsonElement::WriteTo(JsonWriter & Writer) const
{
	if (_Name.GetLength() > 0)
	{
		Writer.WritePropertyName(_Name);
	}
	switch (_Type)
	{
	case JsonNodeType::String:
		Writer.WriteValue(std::get<String>(_Value));
		break;
	case JsonNodeType::Integer:
		Writer.WriteValue(std::get<int32_t>(_Value));
		break;
	case JsonNodeType::Float:
		Writer.WriteValue(std::get<float>(_Value));
		break;
	case JsonNodeType::Double:
		Writer.WriteValue(std::get<double>(_Value));
		break;
	case JsonNodeType::Boolean:
		Writer.WriteValue(std::get<bool>(_Value));
		break;
	case JsonNodeType::Null:
		Writer.WriteNull();
		break;
	}
}
