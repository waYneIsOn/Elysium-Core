#include "JsonArray.hpp"

#ifndef ELYSIUM_CORE_JSON_JSONELEMENT
#include "JsonElement.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONOBJECT
#include "JsonObject.hpp"
#endif

#ifndef ELYSIUM_CORE_CONVERT
#include "../Elysium.Core/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#include "JsonReaderException.hpp"
#endif

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

Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonArray::AddElement(const String & Value)
{
	JsonElement* OwnedElement = new JsonElement(Elysium::Core::String(), Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonArray::AddElement(const int32_t Value)
{
	JsonElement* OwnedElement = new JsonElement(Elysium::Core::String(), Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonArray::AddElement(const float Value)
{
	JsonElement* OwnedElement = new JsonElement(Elysium::Core::String(), Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonArray::AddElement(const double Value)
{
	JsonElement* OwnedElement = new JsonElement(Elysium::Core::String(), Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonArray::AddElement(const bool Value)
{
	JsonElement* OwnedElement = new JsonElement(Elysium::Core::String(), Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonArray::AddElement()
{
	JsonElement* OwnedElement = new JsonElement(Elysium::Core::String());
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}

Elysium::Core::Json::JsonObject & Elysium::Core::Json::JsonArray::AddObject()
{
	JsonObject* OwnedObject = new JsonObject(Elysium::Core::String());
	Elysium::Core::Json::JsonNode::AddChild(*OwnedObject);
	return *OwnedObject;
}

Elysium::Core::Json::JsonArray & Elysium::Core::Json::JsonArray::AddArray()
{
	JsonArray* OwnedArray = new JsonArray(Elysium::Core::String());
	Elysium::Core::Json::JsonNode::AddChild(*OwnedArray);
	return *OwnedArray;
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
			JsonElement* Node = new JsonElement(u"", Elysium::Core::Convert::ToInt32(JsonReader.GetNodeValue(), 10));
			AddChild(*Node);
			break;
		}
		case JsonToken::Float:
		{
			JsonElement* Node = new JsonElement(u"", Elysium::Core::Convert::ToSingle(JsonReader.GetNodeValue()));
			AddChild(*Node);
			break;
		}
		case JsonToken::String:
		{
			JsonElement* Node = new JsonElement(u"", JsonReader.GetNodeValue());
			AddChild(*Node);
			break;
		}
		case JsonToken::Boolean:
		{	// ToDo: what about True/TRUE?
			JsonElement* Node = new JsonElement(u"", JsonReader.GetNodeValue() == u"true" ? true : false);
			AddChild(*Node);
			break;
		}
		case JsonToken::Null:
		{
			JsonElement* Node = new JsonElement(u"");
			AddChild(*Node);
			break;
		}
		case JsonToken::StartedObject:
		{
			JsonObject* Node = new JsonObject(u"");
			AddChild(*Node);
			Node->Load(JsonReader);
			break;
		}
		case JsonToken::StartedArray:
		{
			JsonArray* Node = new JsonArray(u"");
			AddChild(*Node);
			Node->Load(JsonReader);
			break;
		}
		case JsonToken::EndedArray:
			return;
		default:
			throw JsonReaderException();
		}
	}
}

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
