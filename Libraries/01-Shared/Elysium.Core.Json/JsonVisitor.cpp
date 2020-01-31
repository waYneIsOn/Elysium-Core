#include "JsonVisitor.hpp"

Elysium::Core::Json::JsonVisitor::~JsonVisitor()
{ }

Elysium::Core::Json::JsonNode & Elysium::Core::Json::JsonVisitor::Visit(JsonNode & Node)
{
	switch (Node.GetNodeType())
	{
	case JsonNodeType::Array:
		return VisitArray(static_cast<JsonArray&>(Node));
	case JsonNodeType::Boolean:
		return VisitElement(static_cast<JsonElement&>(Node));
	case JsonNodeType::Document:
		return VisitDocument(static_cast<JsonDocument&>(Node));
	case JsonNodeType::Double:
		return VisitElement(static_cast<JsonElement&>(Node));
	case JsonNodeType::Float:
		return VisitElement(static_cast<JsonElement&>(Node));
	case JsonNodeType::Integer:
		return VisitElement(static_cast<JsonElement&>(Node));
	case JsonNodeType::Null:
		return VisitElement(static_cast<JsonElement&>(Node));
	case JsonNodeType::Object:
		return VisitObject(static_cast<JsonObject&>(Node));
	case JsonNodeType::String:
		return VisitElement(static_cast<JsonElement&>(Node));
	default:
		return Node;
	}
}

Elysium::Core::Json::JsonVisitor::JsonVisitor()
{ }

Elysium::Core::Json::JsonArray & Elysium::Core::Json::JsonVisitor::VisitArray(JsonArray & Node)
{
	for (size_t i = 0; i < Node.GetChildCount(); i++)
	{
		Visit(Node.GetChild(i));
	}
	return Node;
}
Elysium::Core::Json::JsonDocument & Elysium::Core::Json::JsonVisitor::VisitDocument(JsonDocument & Node)
{
	for (size_t i = 0; i < Node.GetChildCount(); i++)
	{
		Visit(Node.GetChild(i));
	}
	return Node;
}
Elysium::Core::Json::JsonElement & Elysium::Core::Json::JsonVisitor::VisitElement(JsonElement & Node)
{
	for (size_t i = 0; i < Node.GetChildCount(); i++)
	{
		Visit(Node.GetChild(i));
	}
	return Node;
}
Elysium::Core::Json::JsonObject & Elysium::Core::Json::JsonVisitor::VisitObject(JsonObject & Node)
{
	for (size_t i = 0; i < Node.GetChildCount(); i++)
	{
		Visit(Node.GetChild(i));
	}
	return Node;
}
