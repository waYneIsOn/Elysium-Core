#include "JsonObject.hpp"

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

Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const String & Name, const String & Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const String & Name, const int32_t Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const String & Name, const float Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const String & Name, const double Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const String & Name, const bool Value)
{
	JsonElement* OwnedElement = new JsonElement(Name, Value);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonObject::AddElement(const String & Name)
{
	JsonElement* OwnedElement = new JsonElement(Name);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedElement);
	return *OwnedElement;
}

Elysium::Core::Json::JsonObject & Elysium::Core::Json::JsonObject::AddObject(const String & Name)
{
	JsonObject* OwnedObject = new JsonObject(Name);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedObject);
	return *OwnedObject;
}

Elysium::Core::Json::JsonArray & Elysium::Core::Json::JsonObject::AddArray(const String & Name)
{
	JsonArray* OwnedArray = new JsonArray(Name);
	Elysium::Core::Json::JsonNode::AddChild(*OwnedArray);
	return *OwnedArray;
}

void Elysium::Core::Json::JsonObject::Load(JsonReader & JsonReader)
{
}

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
