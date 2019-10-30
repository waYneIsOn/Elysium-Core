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
#ifdef UNICODE
	static const Elysium::Core::String Name = L"#document";
#else
	static const Elysium::Core::String Name = "#document";
#endif
	return Name;
}
const Elysium::Core::Json::JsonNodeType Elysium::Core::Json::JsonDocument::GetNodeType() const
{
	return JsonNodeType::Document;
}

void Elysium::Core::Json::JsonDocument::WriteTo(JsonWriter & Writer)
{
	Writer.WriteStartObject();
	/*
	for (int i = 0; i < _Children.GetCount(); i++)
	{
		_Children[i].WriteTo(Writer);
	}
	*/
	Writer.WriteEndObject();
}
