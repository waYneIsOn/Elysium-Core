#include "JsonArray.hpp"

Elysium::Core::Json::JsonArray::JsonArray()
	: Elysium::Core::Json::JsonNode(),
	_Name()
{
}
Elysium::Core::Json::JsonArray::JsonArray(const String & Name)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name)
{
}
Elysium::Core::Json::JsonArray::~JsonArray()
{
}

const Elysium::Core::String & Elysium::Core::Json::JsonArray::GetName() const
{
	static const Elysium::Core::String Name = u"#array";
	if (_Name.GetLength() > 0)
	{
		return _Name;
	}
	else
	{
		return Name;
	}
}
const Elysium::Core::Json::JsonNodeType Elysium::Core::Json::JsonArray::GetNodeType() const
{
	return JsonNodeType::Array;
}

void Elysium::Core::Json::JsonArray::WriteTo(JsonWriter & Writer) const
{
	if (_Name.GetLength() > 0)
	{
		Writer.WritePropertyName(_Name);
	}
	Writer.WriteStartArray();
	for (int i = 0; i < _Children.GetCount(); i++)
	{
		_Children[i]->WriteTo(Writer);
	}
	Writer.WriteEndArray();
}
