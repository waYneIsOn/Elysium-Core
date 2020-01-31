#include "ChangingJsonVisitor.hpp"

using namespace Elysium::Core::Json;

UnitTests::Core::Json::ChangingJsonVisitor::ChangingJsonVisitor()
{ }
UnitTests::Core::Json::ChangingJsonVisitor::~ChangingJsonVisitor()
{ }

JsonNode & UnitTests::Core::Json::ChangingJsonVisitor::Visit(JsonNode & Node)
{
	return JsonVisitor::Visit(Node);
}

JsonArray & UnitTests::Core::Json::ChangingJsonVisitor::VisitArray(JsonArray & Node)
{
	return JsonVisitor::VisitArray(Node);
}
JsonDocument & UnitTests::Core::Json::ChangingJsonVisitor::VisitDocument(JsonDocument & Node)
{
	return JsonVisitor::VisitDocument(Node);
}
JsonElement & UnitTests::Core::Json::ChangingJsonVisitor::VisitElement(JsonElement & Node)
{
	switch (Node.GetNodeType())
	{
	case JsonNodeType::Boolean:
		Node.SetValue(!Node.GetValueAsBoolean());
		break;
	case JsonNodeType::Double:
		Node.SetValue(Node.GetValueAsSingle() * -1);
		break;
	case JsonNodeType::Float:
		Node.SetValue(Node.GetValueAsSingle() * -1);
		break;
	case JsonNodeType::Integer:
		Node.SetValue(Node.GetValueAsInt32() * -1);
		break;
	default:
		break;
	}

	return JsonVisitor::VisitElement(Node);
}
JsonObject & UnitTests::Core::Json::ChangingJsonVisitor::VisitObject(JsonObject & Node)
{
	return JsonVisitor::VisitObject(Node);
}
