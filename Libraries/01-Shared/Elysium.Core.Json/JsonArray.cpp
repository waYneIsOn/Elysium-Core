#include "JsonArray.hpp"

#ifndef ELYSIUM_CORE_JSON_JSONELEMENT
#include "JsonElement.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#include "JsonReaderException.hpp"
#endif

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

void Elysium::Core::Json::JsonArray::Load(JsonReader & JsonReader)
{
	while (JsonReader.Read())
	{
		const JsonToken Token = JsonReader.GetToken();
		switch (Token)
		{
		case JsonToken::Integer:
		{
			throw JsonReaderException();
		}
		case JsonToken::Float:
		{
			throw JsonReaderException();
		}
		case JsonToken::String:
		{
			JsonElement* Node = new JsonElement(u"", JsonReader.GetNodeValue());
			AddChild(*Node);
			break;
		}
		case JsonToken::Boolean:
		{
			throw JsonReaderException();
		}
		case JsonToken::Null:
		{
			throw JsonReaderException();
		}
		/*
		case JsonToken::StartedObject:
		case JsonToken::StartedArray:
		*/
		case JsonToken::EndedArray:
			return;
		}
	}
}
