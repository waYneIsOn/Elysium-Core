#include "JsonObject.hpp"

#ifndef ELYSIUM_CORE_CONVERT
#include "../Elysium.Core/Convert.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#include "JsonReaderException.hpp"
#endif


Elysium::Core::Json::JsonObject::JsonObject()
	: Elysium::Core::Json::JsonNode(),
	_Name()
{ }

Elysium::Core::Json::JsonObject::JsonObject(const Elysium::Core::Utf8String& Name)
	: Elysium::Core::Json::JsonNode(),
	_Name(Name)
{ }

Elysium::Core::Json::JsonObject::~JsonObject()
{ }

const Elysium::Core::Utf8String & Elysium::Core::Json::JsonObject::GetName() const
{
	static const Elysium::Core::Utf8String Name = u8"#object";
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
	for (int i = 0; i < _Children.GetLength(); i++)
	{
		_Children[i]->WriteTo(Writer);
	}
	Writer.WriteEndObject();
}

Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const Elysium::Core::Utf8String& Name, const Elysium::Core::Utf8String& Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const Elysium::Core::Utf8String& Name, const int32_t Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const Elysium::Core::Utf8String& Name, const float Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const Elysium::Core::Utf8String& Name, const double Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const Elysium::Core::Utf8String& Name, const bool Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const Elysium::Core::Utf8String& Name)
{
	JsonElement* OwnedElement = new JsonElement(Name);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}

Elysium::Core::Json::JsonObject & Elysium::Core::Json::JsonObject::AddObject(const Elysium::Core::Utf8String& Name)
{
	JsonObject* OwnedObject = new JsonObject(Name);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedObject);
	return *OwnedObject;
}

Elysium::Core::Json::JsonArray & Elysium::Core::Json::JsonObject::AddArray(const Elysium::Core::Utf8String& Name)
{
	JsonArray* OwnedArray = new JsonArray(Name);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedArray);
	return *OwnedArray;
}

void Elysium::Core::Json::JsonObject::Load(JsonReader & JsonReader)
{
	Elysium::Core::Utf8String PropertyName;
	while (JsonReader.Read())
	{
		const JsonToken Token = JsonReader.GetToken();
		switch (Token)
		{
		case JsonToken::PropertyName:
		{
			PropertyName = JsonReader.GetNodeValue();
			break;
		}
		case JsonToken::Integer:
		{
			JsonElement* Node = new JsonElement(PropertyName, Elysium::Core::Convert::ToInt32(JsonReader.GetNodeValue(), 10));
			AddChild(*Node);
			break;
		}
		case JsonToken::Float:
		{
			JsonElement* Node = new JsonElement(PropertyName, Elysium::Core::Convert::ToSingle(JsonReader.GetNodeValue()));
			AddChild(*Node);
			break;
		}
		case JsonToken::String:
		{
			JsonElement* Node = new JsonElement(PropertyName, JsonReader.GetNodeValue());
			AddChild(*Node);
			break;
		}
		case JsonToken::Boolean:
		{	// ToDo: what about True/TRUE?
			JsonElement* Node = new JsonElement(PropertyName, JsonReader.GetNodeValue() == u8"true" ? true : false);
			AddChild(*Node);
			break;
		}
		case JsonToken::Null:
		{
			JsonElement* Node = new JsonElement(PropertyName);
			AddChild(*Node);
			break;
		}
		case JsonToken::StartedArray:
		{
			JsonArray* Node = new JsonArray(PropertyName);
			AddChild(*Node);
			Node->Load(JsonReader);
			break;
		}
		case JsonToken::StartedObject:
		{
			JsonObject* Node = new JsonObject(PropertyName);
			AddChild(*Node);
			Node->Load(JsonReader);
			break;
		}
		case JsonToken::EndedObject:
			return;
		default:
			throw JsonReaderException();
		}
	}
}
