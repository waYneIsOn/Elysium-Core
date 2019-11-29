#include "JsonDocument.hpp"

Elysium::Core::Json::JsonDocument::JsonDocument()
	: Elysium::Core::Json::JsonNode()
{
}
Elysium::Core::Json::JsonDocument::~JsonDocument()
{
}

const Elysium::Core::String & Elysium::Core::Json::JsonDocument::GetName() const
{
	static const Elysium::Core::String Name = u"#document";
	return Name;
}
const Elysium::Core::Json::JsonNodeType Elysium::Core::Json::JsonDocument::GetNodeType() const
{
	return JsonNodeType::Document;
}

void Elysium::Core::Json::JsonDocument::WriteTo(JsonWriter & Writer)
{
	/*
	Writer.WriteStartArray();
	Writer.WriteEndArray();
	*/
	/*
	Writer.WriteStartObject();
	for (int i = 0; i < _Children.GetCount(); i++)
	{
		_Children[i].WriteTo(Writer);
	}
	Writer.WriteEndObject();
	*/
}
