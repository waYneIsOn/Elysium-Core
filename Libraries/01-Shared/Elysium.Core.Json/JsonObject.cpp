#include "JsonObject.hpp"

Elysium::Core::Json::JsonObject::JsonObject()
	: Elysium::Core::Json::JsonNode(),
	_Name()
{
}
Elysium::Core::Json::JsonObject::JsonObject(const String & Name)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name)
{
}
Elysium::Core::Json::JsonObject::~JsonObject()
{
}

const Elysium::Core::String & Elysium::Core::Json::JsonObject::GetName() const
{
	static const Elysium::Core::String Name = u"#object";
	if (_Name.GetLength() > 0)
	{
		return _Name;
	}
	else
	{
		return Name;
	}
}
const Elysium::Core::Json::JsonNodeType Elysium::Core::Json::JsonObject::GetNodeType() const
{
	return JsonNodeType::Object;
}

void Elysium::Core::Json::JsonObject::WriteTo(JsonWriter & Writer) const
{
	if (_Name.GetLength() > 0)
	{
		Writer.WritePropertyName(_Name);
	}
	Writer.WriteStartObject();
	for (int i = 0; i < _Children.GetCount(); i++)
	{
		_Children[i]->WriteTo(Writer);
	}
	Writer.WriteEndObject();
}
