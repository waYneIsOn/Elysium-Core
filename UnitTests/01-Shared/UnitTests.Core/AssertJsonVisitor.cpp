#include "AssertJsonVisitor.hpp"

UnitTests::Core::Json::AssertJsonVisitor::AssertJsonVisitor()
{ }
UnitTests::Core::Json::AssertJsonVisitor::~AssertJsonVisitor()
{ }

JsonNode & UnitTests::Core::Json::AssertJsonVisitor::Visit(JsonNode & Node)
{
	return JsonVisitor::Visit(Node);
}

JsonArray & UnitTests::Core::Json::AssertJsonVisitor::VisitArray(JsonArray & Node)
{
	return JsonVisitor::VisitArray(Node);
}
JsonDocument & UnitTests::Core::Json::AssertJsonVisitor::VisitDocument(JsonDocument & Node)
{
	return JsonVisitor::VisitDocument(Node);
}
JsonElement & UnitTests::Core::Json::AssertJsonVisitor::VisitElement(JsonElement & Node)
{
	return JsonVisitor::VisitElement(Node);
}
JsonObject & UnitTests::Core::Json::AssertJsonVisitor::VisitObject(JsonObject & Node)
{
	return JsonVisitor::VisitObject(Node);
}
